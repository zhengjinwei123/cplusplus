#pragma once
#ifndef _MYAOI_AGENT_H__
#define _MYAOI_AGENT_H__

#include "Detour/DetourNavMesh.h"
#include "Aoi/object.h"
#include "Aoi/point3f.h"

#include <vector>
#include <memory>

namespace aoi
{
	class Filter;
	class Scene;
	class Agent;

	typedef std::vector<Agent*> tAgentPtrVec;

	class Agent : public Object
	{
	public:
		Agent(float width, float height, unsigned id);
		Agent(float x, float y, float z, float width, float height, unsigned id = 0);
		virtual ~Agent();
	public:
		inline int GetId() const { return m_id; }
		inline void SetId(unsigned id) { m_id = id; }

		Point3f& GetPosition();
		void SetTargetPosition(Point3f& target);
		Point3f& GetTargetPosition();

		inline Filter& GetFilter() { return *m_filter; }
		inline void SetFilter(const std::shared_ptr<Filter>& filter) { m_filter = filter; }

		inline void SetScene(Scene* scene) { 
			m_scenePtr = scene;
		}

		// 获取包围盒
	    AABB GetBounds() {
			return GetBound();
		}

		bool Raycast(Point3f& endPos, bool &bHit, Point3f& hitPos);

		//与其他对象的碰撞处理
		void OnHit(Agent *otherAgent, Point3f* pos = nullptr);

		bool SetPosition(Point3f& pos, bool bJustCheck = false);

		void LeaveScene();
		void LeaveGame();
		bool EnterScene(unsigned sceneId,Point3f& position, bool randPos = false);
		bool EnterScene(unsigned scenId);
		bool Move(Point3f& dstPos);
		bool MoveToNext(Point3f& nextPoint);
		void RandomPosition(Point3f& pos);
	private:
		// 移动检测
		bool tryMove(Point3f& endPos, uint64_t& realEndPolyRef, Point3f& readEndPos, bool& bHit);

		// 广播给视野内玩家，
		void broadCast(std::vector<Agent*>& vecList, EAGENT_MOVE_EVENT_TYPE eventType);

		// 寻路 from current position to target position
		void seachPath();

		void polys2Path(dtPolyRef* polys, int nPolys);

		Agent* checkPosByAOI(Point3f& dst);

		tAgentPtrVec& GetObjectsInView(Scene* scentPtr = nullptr);

	private:
		Point3f m_position;
		Point3f m_targetPosition;

		unsigned m_id;
		float m_speed;

		uint64_t m_curPolyRef;
		uint64_t m_endPolyRef;

		std::shared_ptr<Filter> m_filter;
		Scene* m_scenePtr;

		bool m_bStartPosHasSet = false;
		bool m_bEndPosHasSet = false;

		std::vector<Point3f> m_pathList;
		tAgentPtrVec m_objectsInView;
	public:
		std::vector<Point3f>& GetPath()
		{
			return m_pathList;
		}
	};
}


#endif // ! _MYAOI_AGENT_H__
