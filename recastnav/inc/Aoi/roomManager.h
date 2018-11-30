#pragma once
#ifndef _AOI_ROOMMANAGER_H__
#define _AOI_ROOMMANAGER_H__

#include "room.h"
#include <unordered_map>
#include <iostream>

namespace aoi
{
	template<typename PLAYER_TYPE,typename MONSTER_TYPE,typename PLAYER_ID_TYPE,typename MONSTER_ID_TYPE>
	class RoomManager
	{
		using tRoomMap = std::unordered_map<unsigned, Room<PLAYER_TYPE, MONSTER_TYPE, PLAYER_ID_TYPE, MONSTER_ID_TYPE>*>;
	public:
		RoomManager() : m_roomId(1) 
		{
		
		}
		~RoomManager()
		{
			//std::cout << "RoomManager destructor" << std::endl;
		}
		static void Destory()
		{
			if (m_instancePtr)
			{
				delete m_instancePtr;
				m_instancePtr = nullptr;
			}
		}
		RoomManager(const RoomManager&);
		RoomManager& operator = (const RoomManager&);
	public:
		static RoomManager<PLAYER_TYPE, MONSTER_TYPE, PLAYER_ID_TYPE, MONSTER_ID_TYPE> *GetInstance() {
			if (m_instancePtr)
				return m_instancePtr;

			m_instancePtr = new RoomManager<PLAYER_TYPE, MONSTER_TYPE, PLAYER_ID_TYPE, MONSTER_ID_TYPE>();
			return m_instancePtr;
		}
	public:
		Room<PLAYER_TYPE,MONSTER_TYPE, PLAYER_ID_TYPE, MONSTER_ID_TYPE>* CreateRoom(PLAYER_TYPE* ownerPtr) {
			unsigned roomId = m_roomId++;
			Room<PLAYER_TYPE, MONSTER_TYPE, PLAYER_ID_TYPE, MONSTER_ID_TYPE>* roomPtr = new Room<PLAYER_TYPE, MONSTER_TYPE, PLAYER_ID_TYPE, MONSTER_ID_TYPE>(roomId, ownerPtr);
			m_roomMap.insert(std::pair<unsigned, Room<PLAYER_TYPE, MONSTER_TYPE, PLAYER_ID_TYPE, MONSTER_ID_TYPE>*>(roomId, roomPtr));
			return roomPtr;
		}

		Room<PLAYER_TYPE, MONSTER_TYPE, PLAYER_ID_TYPE, MONSTER_ID_TYPE>* GetRoom(unsigned id)
		{
			tRoomMap::iterator itFind = m_roomMap.find(id);
			if (itFind != m_roomMap.end())
			{
				return itFind->second;
			}
			return nullptr;
		}

		void DestroyRoom(unsigned id)
		{
			tRoomMap::iterator itFind = m_roomMap.find(id);
			if (itFind != m_roomMap.end())
			{
				delete itFind->second;
				itFind->second = nullptr;
				m_roomMap.erase(itFind);
			}
		}

		inline const unsigned GetRoomCount() const { return m_roomMap.size(); }
	private:
		static RoomManager<PLAYER_TYPE, MONSTER_TYPE, PLAYER_ID_TYPE, MONSTER_ID_TYPE> * m_instancePtr;
		unsigned m_roomId;

		tRoomMap m_roomMap;
	};

	template<typename PLAYER_TYPE, typename MONSTER_TYPE, typename PLAYER_ID_TYPE, typename MONSTER_ID_TYPE>
	RoomManager<PLAYER_TYPE, MONSTER_TYPE, PLAYER_ID_TYPE, MONSTER_ID_TYPE>* RoomManager<PLAYER_TYPE, MONSTER_TYPE, PLAYER_ID_TYPE, MONSTER_ID_TYPE>::m_instancePtr;
}

#endif // !_AOI_ROOMMANAGER_H__

