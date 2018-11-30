#include "Aoi/defines.h"
#include "Aoi/filter.h"
#include "Aoi/agent.h"
#include "Aoi/scene.h"
#include "Aoi/sceneManager.h"
#include "Recast/Recast.h"
#include "Detour/DetourNavMeshQuery.h"
#include "Detour/DetourCommon.h"

#include <limits>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <iterator>


namespace aoi
{
	static int fixupCorridor(dtPolyRef* path, const int npath, const int maxPath,
		const dtPolyRef* visited, const int nvisited)
	{
		int furthestPath = -1;
		int furthestVisited = -1;

		// Find furthest common polygon.
		for (int i = npath - 1; i >= 0; --i)
		{
			bool found = false;
			for (int j = nvisited - 1; j >= 0; --j)
			{
				if (path[i] == visited[j])
				{
					furthestPath = i;
					furthestVisited = j;
					found = true;
				}
			}
			if (found)
				break;
		}

		// If no intersection found just return current path. 
		if (furthestPath == -1 || furthestVisited == -1)
			return npath;

		// Concatenate paths.	

		// Adjust beginning of the buffer to include the visited.
		const int req = nvisited - furthestVisited;
		const int orig = rcMin(furthestPath + 1, npath);
		int size = rcMax(0, npath - orig);
		if (req + size > maxPath)
			size = maxPath - req;
		if (size)
			memmove(path + req, path + orig, size * sizeof(dtPolyRef));

		// Store visited
		for (int i = 0; i < req; ++i)
			path[i] = visited[(nvisited - 1) - i];

		return req + size;
	}

	// This function checks if the path has a small U-turn, that is,
	// a polygon further in the path is adjacent to the first polygon
	// in the path. If that happens, a shortcut is taken.
	// This can happen if the target (T) location is at tile boundary,
	// and we're (S) approaching it parallel to the tile edge.
	// The choice at the vertex can be arbitrary, 
	//  +---+---+
	//  |:::|:::|
	//  +-S-+-T-+
	//  |:::|   | <-- the step can end up in here, resulting U-turn path.
	//  +---+---+
	static int fixupShortcuts(dtPolyRef* path, int npath, dtNavMeshQuery* navQuery)
	{
		if (npath < 3)
			return npath;

		// Get connected polygons
		static const int maxNeis = 16;
		dtPolyRef neis[maxNeis];
		int nneis = 0;

		const dtMeshTile* tile = 0;
		const dtPoly* poly = 0;
		if (dtStatusFailed(navQuery->getAttachedNavMesh()->getTileAndPolyByRef(path[0], &tile, &poly)))
			return npath;

		for (unsigned int k = poly->firstLink; k != DT_NULL_LINK; k = tile->links[k].next)
		{
			const dtLink* link = &tile->links[k];
			if (link->ref != 0)
			{
				if (nneis < maxNeis)
					neis[nneis++] = link->ref;
			}
		}

		// If any of the neighbour polygons is within the next few polygons
		// in the path, short cut to that polygon directly.
		static const int maxLookAhead = 6;
		int cut = 0;
		for (int i = dtMin(maxLookAhead, npath) - 1; i > 1 && cut == 0; i--) {
			for (int j = 0; j < nneis; j++)
			{
				if (path[i] == neis[j]) {
					cut = i;
					break;
				}
			}
		}
		if (cut > 1)
		{
			int offset = cut - 1;
			npath -= offset;
			for (int i = 1; i < npath; i++)
				path[i] = path[i + offset];
		}

		return npath;
	}


	inline bool inRange(const float* v1, const float* v2, const float r, const float h)
	{
		const float dx = v2[0] - v1[0];
		const float dy = v2[1] - v1[1];
		const float dz = v2[2] - v1[2];
		return (dx*dx + dz*dz) < r*r && fabsf(dy) < h;
	}

	static bool getSteerTarget(dtNavMeshQuery* navQuery, const float* startPos, const float* endPos,
		const float minTargetDist,
		const dtPolyRef* path, const int pathSize,
		float* steerPos, unsigned char& steerPosFlag, dtPolyRef& steerPosRef,
		float* outPoints = 0, int* outPointCount = 0)
	{
		// Find steer target.
		static const int MAX_STEER_POINTS = 3;
		float steerPath[MAX_STEER_POINTS * 3];
		unsigned char steerPathFlags[MAX_STEER_POINTS];
		dtPolyRef steerPathPolys[MAX_STEER_POINTS];
		int nsteerPath = 0;
		navQuery->findStraightPath(startPos, endPos, path, pathSize,
			steerPath, steerPathFlags, steerPathPolys, &nsteerPath, MAX_STEER_POINTS);
		if (!nsteerPath)
			return false;

		if (outPoints && outPointCount)
		{
			*outPointCount = nsteerPath;
			for (int i = 0; i < nsteerPath; ++i)
				dtVcopy(&outPoints[i * 3], &steerPath[i * 3]);
		}


		// Find vertex far enough to steer to.
		int ns = 0;
		while (ns < nsteerPath)
		{
			// Stop at Off-Mesh link or when point is further than slop away.
			if ((steerPathFlags[ns] & DT_STRAIGHTPATH_OFFMESH_CONNECTION) ||
				!inRange(&steerPath[ns * 3], startPos, minTargetDist, 1000.0f))
				break;
			ns++;
		}
		// Failed to find good point to steer to.
		if (ns >= nsteerPath)
			return false;

		dtVcopy(steerPos, &steerPath[ns * 3]);
		steerPos[1] = startPos[1];
		steerPosFlag = steerPathFlags[ns];
		steerPosRef = steerPathPolys[ns];

		return true;
	}

	Agent::Agent(float width, float height, unsigned id) :
		Agent(0,0,0,width,height,id)
	{
		
	}

	Agent::Agent(float x, float y, float z,float width, float height, unsigned id) :
		Object(AABB(x,z,width,height), id),
		m_scenePtr(nullptr),
		m_curPolyRef(0),
		m_endPolyRef(0),
		m_id(id)
	{

		SetPosition(Point3f(x, y, z));

		m_filter = std::make_shared<Filter>();
		m_filter->SetExcludeFlags(POLYFLAGS_ALL ^ POLYFLAGS_DISABLED);
		m_filter->SetExcludeFlags(0);

		// Change costs.
		m_filter->SetAreaCost(POLYAREA_GROUND, 1.0f);
		m_filter->SetAreaCost(POLYAREA_WATER, 10.0f);
		m_filter->SetAreaCost(POLYAREA_ROAD, 1.0f);
		m_filter->SetAreaCost(POLYAREA_DOOR, 1.0f);
		m_filter->SetAreaCost(POLYAREA_GRASS, 2.0f);
		m_filter->SetAreaCost(POLYAREA_JUMP, 1.5f);
	}

	Agent::~Agent()
	{
		LeaveGame();
	}

	// 离开游戏
	void Agent::LeaveGame()
	{
		LeaveScene();
	}

	// 离开场景
	void Agent::LeaveScene()
	{
		if (m_scenePtr)
		{
			if (Scene *scene = SceneManager::GetInstance()->GetScene(m_scenePtr->GetId()))
			{
				this->m_pathList.clear();

				// 广播
				broadCast(GetObjectsInView(scene), EAMET_LEAVE_SCENE);

				scene->RemoveAgent(m_id);
			}
		}
	}

	bool Agent::EnterScene(unsigned sceneId)
	{
		return EnterScene(sceneId, m_position,true);
	}

	// 进入场景
	bool Agent::EnterScene(unsigned sceneId,Point3f& position,bool randPos)
	{
		// 当前玩家没有处在任何场景中
		if (!m_scenePtr)
		{
			if (Scene *scene = SceneManager::GetInstance()->GetScene(sceneId))
			{
				m_scenePtr = scene;
				if (randPos)
				{
					RandomPosition(position);
				}
				if(this->SetPosition(position))
				{
					scene->AddAgent(this);
					// 广播
					broadCast(GetObjectsInView(scene), EAMET_ENTER_SCENE);

					return true;
				}
				m_scenePtr = nullptr;
			}
			return false;
		}

		// 当前玩家处于某个场景中
		if (Scene *scene = SceneManager::GetInstance()->GetScene(sceneId))
		{
			// 处于当前场景中,只需要修改位置即可
			if (m_scenePtr->GetId() == scene->GetId())
			{
				if (this->SetPosition(position))
				{
					return true;
				}
				return false;
			}
			else
			{
				// 离开之前的场景，加入新场景
				LeaveScene();
				m_scenePtr = scene;
				if (this->SetPosition(position))
				{
					// 广播
					broadCast(GetObjectsInView(scene), EAMET_ENTER_SCENE);

					scene->AddAgent(this);
					return true;
				}
			}
		}

		return false;
	}


	float randf()
	{
		return (float)(rand() / (float)RAND_MAX);
	}

	void Agent::RandomPosition(Point3f& pos)
	{
	LABEL_RANDOM:
		float halfExtents[3] = { 2,4,2 };
		float randPos[3];
		m_scenePtr->GetDetour().RandomPosition(halfExtents, &m_filter->Get(), randf, m_curPolyRef, randPos);
	
		pos.x = randPos[0];
		pos.y = randPos[1];
		pos.z = randPos[2];
		if (!SetPosition(pos))
		{
			goto LABEL_RANDOM;
		}
	}

	// 实际移动到下一个临近坐标点
	bool Agent::MoveToNext(Point3f& nextPoint)
	{
		if (nextPoint.IsZero())
		{
			return false;
		}

		// 玩家间的碰撞检测,只是检测，不设置为新坐标
		if (!SetPosition(nextPoint,true))
		{
			return false;
		}

		// 障碍物检测
		bool bHit;
		uint64_t realEndPolyRef;
		Point3f realEndPos;
		if (!tryMove(nextPoint, realEndPolyRef, realEndPos, bHit)) {
			return false;
		}

		// 碰撞到障碍物
		if (bHit)
		{
			return false;
		}

		tAgentPtrVec oldViewAgentSet = GetObjectsInView();

		m_curPolyRef = realEndPolyRef;
		m_position = realEndPos;

		// 校验位置是否有合适的偏移，如果没有偏移，不设定为新坐标
		if (fabs( GetX() - m_position.x) >= std::numeric_limits<float>::epsilon() || fabs(GetZ() - m_position.z) >= std::numeric_limits<float>::epsilon())
		{
			if (!SetPosition(m_position))
			{
				assert(false);
				return false;
			}

			tAgentPtrVec newViewAgentSet = GetObjectsInView();
			/*Set(m_position);
			m_scenePtr->Update(this);*/

			// 通知视野范围内的玩家
			// 1. 新范围与老范围节点的交集看见 agent 在移动 （old X new）
			tAgentPtrVec result;
			std::set_intersection(oldViewAgentSet.begin(), oldViewAgentSet.end(), newViewAgentSet.begin(), newViewAgentSet.end(), std::inserter(result, result.begin()));
			broadCast(result, EAMET_MOVE_SCENE);

			// 2. 老范围节点 与 新范围节点的差集看见 agent 离开 (old - new)
			result.clear();
			std::set_difference(oldViewAgentSet.begin(), oldViewAgentSet.end(), newViewAgentSet.begin(), newViewAgentSet.end(), std::inserter(result, result.begin()));
			broadCast(result, EAMET_MOVE_SCENE);

			// 3. 新范围节点 与 老范围节点的差集看见 agent 进入 (new - old)
			result.clear();
			std::set_difference(newViewAgentSet.begin(), newViewAgentSet.end(), oldViewAgentSet.begin(), oldViewAgentSet.end(), std::inserter(result, result.begin()));
			broadCast(result, EAMET_ENTER_SCENE);
		}
		return true;
	}

	// 广播给视野内玩家，
	void Agent::broadCast(tAgentPtrVec& vecList, EAGENT_MOVE_EVENT_TYPE eventType)
	{
		if (vecList.empty())
		{
			return;
		}

		tAgentPtrVec::iterator it = vecList.begin();
		for (; it != vecList.end(); ++it)
		{
			// 自己忽略
			if ((*it)->GetId() == GetId())
			{
				continue;
			}

			//std::cout << GetId()<< "(event:"<< eventType<<")-->广播给视野内玩家:" <<(*it)->GetId()<< endl;
		}
	}


	// 场景内移动，获取一个路径
	bool Agent::Move(Point3f& dstPos)
	{
		if (!m_scenePtr)
		{
			return false;
		}

		// 在当前位置移动0距离
		if (m_position == dstPos)
		{
			return false;
		}

		// 设置目标位置
		SetTargetPosition(dstPos);
		// 寻路
		seachPath();

		if (m_pathList.empty())
		{
			return false;
		}
		return true;
	}


	bool Agent::SetPosition(Point3f& pos,bool bJustCheck)
	{
		if (m_scenePtr)
		{ 
			if (!checkPosByAOI(pos))
			{
				if (bJustCheck) {
					return true;
				}
				float position[3] = { pos.x,pos.y,pos.z };
				float halfExtents[3] = { 2,4,2 };// { GetBound().GetHalfDims().x, GetBound().GetHalfDims().y, GetBound().GetHalfDims().z };
				float curPosition[3] = { GetBound().GetX(),GetBound().GetY(),GetBound().GetZ()};
				m_scenePtr->GetDetour().GetPoly(position, halfExtents, m_filter->Get(), m_curPolyRef, curPosition);

				Set(pos);
				//GetBound().Set(pos);
				m_position = pos;
				m_scenePtr->Update(this);

				m_bStartPosHasSet = true;
				return true;
			}
		}
		return false;
	}

	// 射线测试，用于发射技能等
	bool Agent::Raycast(Point3f& endPos, bool &bHit, Point3f& hitPos)
	{
		if (m_scenePtr)
		{
			float _pos[3] = { GetBound().GetX(),GetBound().GetY(),GetBound().GetZ() };
			float _endPos[3] = { endPos.x,endPos.y,endPos.z};
			float _hitPos[3];
			bool bReturn = m_scenePtr->GetDetour().Raycast(
				m_curPolyRef,
				_pos,
				_endPos,
				m_filter->Get(),
				bHit,
				_hitPos
			);
			hitPos.x = _hitPos[0];
			hitPos.y = _hitPos[1];
			hitPos.z = _hitPos[2];

			return false;;
		}
		return false;
	}

	// 寻路 from current position to target position
	void Agent::seachPath()
	{
		if (!m_scenePtr)
		{
			return;
		}
		m_pathList.clear();

		float curPosition[3] = { GetBound().GetX(),GetBound().GetY(),GetBound().GetZ() };
		float half[3] = { 2,4,2 };// { GetBound().GetHalfDims().x, GetBound().GetHalfDims().y, GetBound().GetHalfDims().z };
		float endPosition[3] = { m_targetPosition.x, m_targetPosition.y,m_targetPosition.z };
	
		if (m_bStartPosHasSet)
		{
			m_scenePtr->GetDetour().GetQuery()->findNearestPoly(curPosition, half, &m_filter->Get(), (dtPolyRef*)&m_curPolyRef, 0);
		}
		else
			m_curPolyRef = 0;

		if (m_bEndPosHasSet)
		{
			m_scenePtr->GetDetour().GetQuery()->findNearestPoly(endPosition, half, &m_filter->Get(), (dtPolyRef*)&m_endPolyRef, 0);
		}
		else
			m_endPolyRef = 0;

		if (m_bStartPosHasSet && m_bEndPosHasSet && m_curPolyRef && m_endPolyRef)
		{
			int nPolys = 0;
			dtPolyRef polys[MAX_POLYS];
			memset(polys, 0, sizeof(polys) / sizeof(dtPolyRef));
			m_scenePtr->GetDetour().GetQuery()->findPath(m_curPolyRef, m_endPolyRef, curPosition, endPosition, &m_filter->Get(), polys, &nPolys, MAX_POLYS);

			polys2Path(polys, nPolys);
		}
	}


	// 移动检测
	bool Agent::tryMove(Point3f& endPos, uint64_t& realEndPolyRef, Point3f& realEndPos, bool& bHit)
	{
		if (m_scenePtr)
		{
			float curpos[3] = { GetBound().GetX(),GetBound().GetY(),GetBound().GetZ()};
			float _endPos[3] = { endPos.x,endPos.y,endPos.z};
			float _realEndPos[3];

			float halfExtents[3] = { 2,4,2 };// { GetBound().GetHalfDims().x, GetBound().GetHalfDims().y, GetBound().GetHalfDims().z};

			bool bRet = m_scenePtr->GetDetour().TryMove(m_curPolyRef, curpos, _endPos, halfExtents, m_filter->Get(), realEndPolyRef, _realEndPos, bHit);

			realEndPos.x = _realEndPos[0];
			realEndPos.y = _realEndPos[1];
			realEndPos.z = _realEndPos[2];

			// 障碍物
			if (bHit)
			{
				OnHit(nullptr, &endPos);
			}
			return bRet;
		}
		return false;
	}


	void Agent::polys2Path(dtPolyRef* polys, int nPolys)
	{
		int  nsmoothPath = 0;
		float smoothPath[MAX_SMOOTH * 3];

		if (nPolys)
		{
			float curPosition[3] = {	GetBound().GetX(),GetBound().GetY(),GetBound().GetZ() };
			float half[3] = { 2,4,2 };// { GetBound().GetHalfDims().x, GetBound().GetHalfDims().y, GetBound().GetHalfDims().z };
			float endPosition[3] = { m_targetPosition.x, m_targetPosition.y,m_targetPosition.z };


			// Iterate over the path to find smooth path on the detail mesh surface.
			dtPolyRef _polys[MAX_POLYS];
			memcpy(_polys, polys, sizeof(dtPolyRef)*nPolys);
			int _npolys = nPolys;

			float iterPos[3], targetPos[3];
			m_scenePtr->GetDetour().GetQuery()->closestPointOnPoly(m_curPolyRef, curPosition, iterPos, 0);
			m_scenePtr->GetDetour().GetQuery()->closestPointOnPoly(_polys[_npolys - 1], endPosition, targetPos, 0);

			static const float STEP_SIZE = 0.5f;
			static const float SLOP = 0.01f;

			nsmoothPath = 0;

			dtVcopy(&smoothPath[nsmoothPath * 3], iterPos);
			nsmoothPath++;

			// Move towards target a small advancement at a time until target reached or
			// when ran out of memory to store the path.
			while (_npolys && nsmoothPath < MAX_SMOOTH)
			{
				// Find location to steer towards.
				float steerPos[3];
				unsigned char steerPosFlag;
				dtPolyRef steerPosRef;

					if (!getSteerTarget(m_scenePtr->GetDetour().GetQuery(), iterPos, targetPos, SLOP,
						_polys, _npolys, steerPos, steerPosFlag, steerPosRef))
						break;

				bool endOfPath = (steerPosFlag & DT_STRAIGHTPATH_END) ? true : false;
				bool offMeshConnection = (steerPosFlag & DT_STRAIGHTPATH_OFFMESH_CONNECTION) ? true : false;

				// Find movement delta.
				float delta[3], len;
				dtVsub(delta, steerPos, iterPos);
				len = dtMathSqrtf(dtVdot(delta, delta));
				// If the steer target is end of path or off-mesh link, do not move past the location.
				if ((endOfPath || offMeshConnection) && len < STEP_SIZE)
					len = 1;
				else
					len = STEP_SIZE / len;
				float moveTgt[3];
				dtVmad(moveTgt, iterPos, delta, len);

				// Move
				float result[3];
				dtPolyRef visited[16];
				int nvisited = 0;
				bool bHit;
				m_scenePtr->GetDetour().GetQuery()->moveAlongSurface(_polys[0], iterPos, moveTgt, &m_filter->Get(),
					result, visited, &nvisited, 16, bHit);

				_npolys = fixupCorridor(_polys, _npolys, MAX_POLYS, visited, nvisited);
				_npolys = fixupShortcuts(_polys, _npolys, m_scenePtr->GetDetour().GetQuery());

				float h = 0;
				m_scenePtr->GetDetour().GetQuery()->getPolyHeight(_polys[0], result, &h);
				result[1] = h;
				dtVcopy(iterPos, result);

				// Handle end of path and off-mesh links when close enough.
				if (endOfPath && inRange(iterPos, steerPos, SLOP, 1.0f))
				{
					// Reached end of path.
					dtVcopy(iterPos, targetPos);
					if (nsmoothPath < MAX_SMOOTH)
					{
						dtVcopy(&smoothPath[nsmoothPath * 3], iterPos);
						nsmoothPath++;
					}
					break;
				}
				else if (offMeshConnection && inRange(iterPos, steerPos, SLOP, 1.0f))
				{
					// Reached off-mesh connection.
					float startPos[3], endPos[3];

					// Advance the path up to and over the off-mesh connection.
					dtPolyRef prevRef = 0, polyRef = _polys[0];
					int npos = 0;
					while (npos < _npolys && polyRef != steerPosRef)
					{
						prevRef = polyRef;
						polyRef = _polys[npos];
						npos++;
					}
					for (int i = npos; i < _npolys; ++i)
						_polys[i - npos] = _polys[i];
					_npolys -= npos;

					// Handle the connection.
					dtStatus status = m_scenePtr->GetDetour().GetMesh()->getOffMeshConnectionPolyEndPoints(prevRef, polyRef, startPos, endPos);
					if (dtStatusSucceed(status))
					{
						if (nsmoothPath < MAX_SMOOTH)
						{
							dtVcopy(&smoothPath[nsmoothPath * 3], startPos);
							nsmoothPath++;
							// Hack to make the dotted path not visible during off-mesh connection.
							if (nsmoothPath & 1)
							{
								dtVcopy(&smoothPath[nsmoothPath * 3], startPos);
								nsmoothPath++;
							}
						}
						// Move position at the other side of the off-mesh link.
						dtVcopy(iterPos, endPos);
						float eh = 0.0f;
						m_scenePtr->GetDetour().GetQuery()->getPolyHeight(_polys[0], iterPos, &eh);
						iterPos[1] = eh;
					}
				}

				// Store results.
				if (nsmoothPath < MAX_SMOOTH)
				{
					dtVcopy(&smoothPath[nsmoothPath * 3], iterPos);
					nsmoothPath++;
				}
			}
		}

		for (int i = 0; i < nsmoothPath; ++i) {
			Point3f position;
			position.x = smoothPath[i * 3];
			position.y = smoothPath[i * 3 + 1];
			position.z = smoothPath[i * 3 + 2];
			m_pathList.push_back(position);
		}
		
	}

	// 碰撞检测
	/************************************************************************/
	/*              dst: 目标坐标的中心点                                                        */
	/************************************************************************/
	Agent* Agent::checkPosByAOI(Point3f& dst)
	{
		m_scenePtr->GetObjectsInBound(AABB(dst.x, dst.z, GetBound().GetWidth(), GetBound().GetHeight()));

		if (!m_scenePtr->m_foundObjects.empty())
		{
			for (auto &obj : m_scenePtr->m_foundObjects)
			{
				if (obj == this)
				{
					continue;
				}
				if(obj->GetBound().Intersects(AABB(dst.x, dst.z, GetBound().GetWidth(), GetBound().GetHeight())))
				{
					OnHit(obj);
					return obj;
				}
			}
		}
		return nullptr;
	}

	// 获取视野内玩家s
	std::vector<Agent*>& Agent::GetObjectsInView(Scene* scentPtr)
	{
		if (!scentPtr)
			scentPtr = m_scenePtr;

		m_objectsInView.clear();

		Point3f center;
		Vec3f ct = GetBound().GetCenter();
		center.x = ct.x;
		center.y = ct.y;
		center.z = ct.z;

		m_objectsInView = scentPtr->GetObjectsInBound(AABB(center.x, center.z, AGENT_VIEW_WIDTH,AGENT_VIEW_HEIGHT));
		return m_objectsInView;
	}

	//与其他对象的碰撞处理
	void Agent::OnHit(Agent *otherAgent, Point3f* pos)
	{
		if (otherAgent)
		{
			/*	cout << "玩家碰撞:" << m_id << "与" << otherAgent->GetId() << endl;
				cout << m_id << ":(" << GetX() << "," << GetY() << "," << GetZ() << ",|" << GetWidth() << "," << GetHeight() << endl;
				cout << otherAgent->GetId() << ":(" << otherAgent->GetX() << "," << otherAgent->GetY() << "," << otherAgent->GetZ() << ",|" << otherAgent->GetWidth() << "," << otherAgent->GetHeight() << endl;
			*/
		}
		else
		{
			//cout << "有障碍物" << *pos << endl;
		}
	}

	 Point3f& Agent::GetPosition() {
		m_position.x = GetBound().GetX();
		m_position.y = GetBound().GetY();
		m_position.z = GetBound().GetZ();
		return m_position;
	}

	 void Agent::SetTargetPosition(Point3f& target) 
	 {
		 m_targetPosition = target; 
		 m_bEndPosHasSet = true;
	 }

	 Point3f& Agent::GetTargetPosition() 
	 { 
		 return m_targetPosition; 
	 }
}