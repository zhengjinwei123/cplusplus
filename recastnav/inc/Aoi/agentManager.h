#pragma once
#ifndef _MYAOI_AGENT_MANAGER_H__
#define _MYAOI_AGENT_MANAGER_H__

#include "Aoi/agent.h"

#include <mutex>
#include <unordered_map>

namespace aoi
{

	typedef std::unordered_map<unsigned, Agent*> tAgentMap;
	class AgentManager
	{
	public:
		~AgentManager() {}
		AgentManager(const AgentManager&);
		AgentManager& operator=(const AgentManager&);
	public:
		static AgentManager* GetInstance();
		static void Destroy();
	public:
		Agent* GetAgent(unsigned id);
		Agent* CreateAgent(unsigned id,float width,float height);
		bool DestroyAgent(unsigned id);
		void Release();
	private:
		AgentManager() {}
	private:
		static AgentManager* m_instancePtr;
		static std::mutex m_mutex;

		tAgentMap m_mapAgent;
	};
}



#endif // !_MYAOI_AGENT_MANAGER_H__
