#pragma once
#ifndef _AOI_ROOM_H__
#define _AOI_ROOM_H__

#include "player.h"
#include "point3f.h"
#include "defines.h"

#include <unordered_map>
#include <assert.h>

namespace aoi
{
	template<typename PLAYER_TYPE,typename MONSTER_TYPE,typename PLAYER_ID_TYPE,typename MONSTER_ID_TYPE>
	class Room
	{
		using tPlayerMap = std::unordered_map<PLAYER_ID_TYPE,PLAYER_TYPE*>;
		using tMonsterMap = std::unordered_map<MONSTER_ID_TYPE, MONSTER_TYPE*>;
		typedef void(*tPlayerEventCallbackFunc)(PLAYER_ID_TYPE, PLAYER_ID_TYPE,const Point3f&, EAGENT_MOVE_EVENT_TYPE);
		typedef void(*tMonsterEventCallbackFunc)(PLAYER_ID_TYPE, PLAYER_ID_TYPE, const Point3f&, EMONSTER_EVENT_TYPE);
	public:
		Room(unsigned id, PLAYER_TYPE* owner = nullptr) : m_id(id), m_ownerPtr(owner)
		{
			m_playerMap.insert(std::pair<PLAYER_ID_TYPE, PLAYER_TYPE*>(m_ownerPtr->GetId(), m_ownerPtr));
		}
		~Room()
		{
			Clean();
		}
	public:
		inline const unsigned  GetTotalPlayers() const { return m_playerVec.size();}
		inline const unsigned GetTotalMonsters() const { return m_enemyMap.size(); }

		inline const PLAYER_TYPE* GetOwner() const { return m_ownerPtr; }
		inline void SetOwner(PLAYER_TYPE* owner) { m_ownerPtr = owner; }

		// ��ҽ��뷿��,�㲥������
		void PlayerEnter(PLAYER_TYPE* player, tPlayerEventCallbackFunc func)
		{
			tPlayerMap::iterator itFind = m_playerMap.find(player->GetId());
			if (itFind != m_playerMap.end())
			{
				return;
			}

			m_playerMap.insert(std::pair<PLAYER_ID_TYPE, PLAYER_TYPE*>(player->GetId(), player));

			tPlayerMap::iterator it = m_playerMap.begin();
			for (; it != m_playerMap.end(); ++it)
			{
				if (it->second->GetId() == player->GetId())
				{
					continue;
				}
				(*func)(it->second->GetId(), player->GetId(),player->GetPosition(), EAMET_ENTER_SCENE);
			}
		}

		// ����뿪����,�㲥������
		void PlayerLeave(PLAYER_ID_TYPE id, tPlayerEventCallbackFunc func)
		{
			tPlayerMap::iterator itFind = m_playerMap.find(id);
			if (itFind == m_playerMap.end())
			{
				return;
			}

			delete itFind->second;
			itFind->second = nullptr;
			m_playerMap.erase(itFind);


			Point3f position;
			tPlayerMap::iterator it = m_playerMap.begin();
			for (; it != m_playerMap.end(); ++it)
			{
				(*func)(it->second->GetId(), itFind->second->GetId(),position, EAMET_LEAVE_SCENE);
			}

		}

		// ����ƶ����㲥������
		void PlayerMove(PLAYER_ID_TYPE id, Point3f& position, tPlayerEventCallbackFunc func)
		{
			tPlayerMap::iterator itFind = m_playerMap.find(id);
			if (itFind == m_playerMap.end())
			{
				return;
			}

			Point3f position;

			tPlayerMap::iterator it = m_playerMap.begin();
			for (; it != m_playerMap.end(); ++it)
			{
				if (it->second->GetId() == id)
				{
					continue;
				}

				(*func)(it->second->GetId(), itFind->second->GetId(), position, EAMET_MOVE_SCENE);
			}
		}

		// �����ƶ����㲥���������,����֪ͨ����������
		void MonsterMove(MONSTER_ID_TYPE id, Point3f& position, tMonsterEventCallbackFunc func)
		{
			tMonsterMap::iterator itMonsterFind = m_monsterMap.find(id);
			if (itMonsterFind == m_monsterMap.end())
			{
				return;
			}
			tPlayerMap::iterator it = m_playerMap.begin();
			for (; it != m_playerMap.end(); ++it)
			{
				// ����Ҫ֪ͨ������
				if (it->second->GetId() == m_ownerPtr->GetId())
				{
					continue;
				}

				(*func)(it->second->GetId(), id, position, EMET_MOVE_SCENE);
			}
		}

		// ��������
		void MonsterDead(MONSTER_ID_TYPE id, tMonsterEventCallbackFunc func)
		{
			tMonsterMap::iterator itMonsterFind = m_monsterMap.find(id);
			if (itMonsterFind == m_monsterMap.end())
			{
				return;
			}

			delete itMonsterFind->second;
			itMonsterFind->second = nullptr;
			m_monsterMap.erase(itMonsterFind);

			Point3f position;

			tPlayerMap::iterator it = m_playerMap.begin();
			for (; it != m_playerMap.end(); ++it)
			{
				// ����Ҫ֪ͨ������
				if (it->second->GetId() == m_ownerPtr->GetId())
				{
					continue;
				}

				(*func)(it->second->GetId(), id, position, EMET_DEAD_SCENE);
			}
		}

		//���ع�����Ϣ
		void InitMonster()
		{

		}

		inline const unsigned GetId() const { return m_id; } 

   private:
		// ���ٷ���
		void Clean() 
		{
			tPlayerMap::iterator it = m_playerMap.begin();
			for (; it != m_playerMap.end(); ++it)
			{
				delete it->second;
				it->second = nullptr;
			}
			m_ownerPtr = nullptr;
			m_playerMap.clear();

			tMonsterMap::iterator itm = m_monsterMap.begin();
			for (; itm != m_monsterMap.end(); ++itm)
			{
				delete itm->second;
				itm->second = nullptr;
			}
			m_monsterMap.clear();
		}

	private:
		unsigned m_id; // ����id
		PLAYER_TYPE* m_ownerPtr;//����

		tPlayerMap m_playerMap;// �����Ϣ�б�
		tMonsterMap m_monsterMap;// �����б�
	};
}


#endif // !_AOI_ROOM_H__
