#include "Aoi/agentManager.h"

namespace aoi
{
	std::mutex  AgentManager::m_mutex;
	AgentManager* AgentManager::m_instancePtr;

	AgentManager*AgentManager::GetInstance()
	{
		if (NULL == m_instancePtr) {
			std::lock_guard<std::mutex> lock(m_mutex);
			if (NULL == m_instancePtr) {
				m_instancePtr = new AgentManager();
			}
		}
		return m_instancePtr;
	}

	void AgentManager::Destroy()
	{
		if (m_instancePtr) {
			std::lock_guard<std::mutex> lock(m_mutex);
			if (m_instancePtr) {
				delete m_instancePtr;
				m_instancePtr = NULL;
			}
		}
	}

	Agent* AgentManager::GetAgent(unsigned id)
	{
		tAgentMap::iterator it = m_mapAgent.find(id);
		if (it != m_mapAgent.end())
		{
			return it->second;
		}
		return nullptr;
	}
	Agent* AgentManager::CreateAgent(unsigned id, float width, float height)
	{
		Agent* agentPtr = new Agent(width, height, id);
		m_mapAgent.insert(std::pair<unsigned, Agent*>(id, agentPtr));

		return agentPtr;
	}
	bool AgentManager::DestroyAgent(unsigned id)
	{
		tAgentMap::iterator it = m_mapAgent.find(id);
		if (it != m_mapAgent.end())
		{
			if (it->second)
			{
				delete it->second;
				it->second = nullptr;
			}
			m_mapAgent.erase(it);
			return true;
		}
		return false;
	}

	void AgentManager::Release()
	{
		tAgentMap::iterator it = m_mapAgent.begin();

		for (; it != m_mapAgent.end(); ++it)
		{
			delete it->second;
			it->second = nullptr;
		}
		m_mapAgent.clear();
	}
}