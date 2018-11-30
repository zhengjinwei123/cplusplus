#pragma once
#ifndef _MYAOI_SCENE_H__
#define _MYAOI_SCENE_H__

#include "Aoi/defines.h"
#include "Aoi/quadTree.h"
#include "Aoi/agent.h"
#include "Aoi/detour.h"
#include "Aoi/filter.h"

#include <memory>
#include <unordered_map>
#include <iostream>

using namespace std;

namespace aoi
{
	class Scene : public QuadTree
	{
	public:
		Scene(bool dynamicScene  = false) :
			QuadTree(AABB(100, 100), 10, 10),
			m_isDynamicScene(dynamicScene),
			m_detour(new CDetour(!dynamicScene,2048))
		{
			if (m_isDynamicScene)
			{
				m_detour->SetHeightMode(HEIGHT_MODE_2);
			}
		}
		~Scene(){
			if (m_detour)
			{
				delete m_detour; m_detour = nullptr;
			}
		}

		int Load(const char* path)
		{
			int retCode = m_detour->Load(path);
			if (!retCode)
			{
				// 设置场景包围框边界
				float* bmin = m_detour->GetBoundsMin();
				float* bmax = m_detour->GetBoundsMax();

				/*	cout << "Scene load: min(" << bmin[0] << "," << bmin[1] << "," << bmin[2] << ")" << endl;
					cout << "Scene load: max(" << bmax[0] << "," << bmax[1] << "," << bmax[2] << ")" << endl;*/

				m_bound.SetLowerBound(Vec3f(bmin[0], bmin[1], bmin[2]));
				m_bound.SetUpperBound(Vec3f(bmax[0], bmax[1], bmax[2]));

				/*	cout << "scene width:" << GetWidth() << endl;
					cout << "scene height:" << GetHeight() << endl;*/
			}
			return retCode;
		}

		const Vec3f& GetLowerBound()  { return m_bound.GetLowerBound(); }
		const Vec3f& GetUpperBound() { return m_bound.GetUpperBound(); }
		const float GetWidth() { return m_bound.GetDims().x; }
		const float GetHeight() { return m_bound.GetDims().z; }

		void AddAgent(Agent *agent)
		{
			if (agent) {
				m_agents[agent->GetId()] = agent;
				agent->SetScene(this);
				Insert(agent);
			}
		}
		const Agent* GetAgent(unsigned id)
		{
			auto it = m_agents.find(id);
			if (it != m_agents.end()) {
				return it->second;
			}
			return nullptr;
		}
		void RemoveAgent(unsigned id)
		{
			auto it = m_agents.find(id);
			if (it != m_agents.end())
			{
				Remove(it->second);
				m_agents.erase(it);
			}
		}

		float* GetBoundsMin(){ return  m_detour->GetBoundsMin(); }
		float* GetBoundsMax()
		{
			return m_detour->GetBoundsMax();
		}

		unsigned int AddCapsuleObstacle(const float pos[3], const float radius, const float height) {
			if (m_isDynamicScene)
			{
				return m_detour->AddCapsuleObstacle(pos, radius, height);
			}
			return 0;
		}
		unsigned int AddBoxObstacle(const float bmin[3], const float bmax[3])
		{
			if (m_isDynamicScene)
			{
				return m_detour->AddBoxObstacle(bmin, bmax);
			}
			return 0;
		}
		unsigned int AddBoxObstacle(const float center[3], const float halfExtents[3], const float yRadians)
		{
			if (m_isDynamicScene)
			{
				return m_detour->AddBoxObstacle(center, halfExtents, yRadians);
			}
			return 0;
		}
		void RemoveObstacle(unsigned int obstacleId)
		{
			if (m_isDynamicScene)
			{
				m_detour->RemoveObstacle(obstacleId);
			}
		}

	public:
		inline void SetId(unsigned id) { m_id = id; }
		inline unsigned GetId() const { return m_id; }

		inline  CDetour& GetDetour() { return *m_detour; }
	private:
		CDetour*  m_detour;
		std::unordered_map<unsigned, Agent*> m_agents;
	private:
		unsigned m_id;
		bool m_isDynamicScene;
	};
}
#endif // !_MYAOI_SCENE_H__
