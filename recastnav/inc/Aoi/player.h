#pragma once
#ifndef _AOI_PLAYER_H__
#define _AOI_PLAYER_H__

#include "object1.h"
#include <iostream>

namespace aoi
{
	template<typename PLAYER_ID_TYPE>
	class Player : public Object1<PLAYER_ID_TYPE>
	{
	public:
		Player(PLAYER_ID_TYPE id) : Object1(id) {}
		virtual ~Player() 
		{
			//std::cout << "player destructor" << std::endl;
		}
	};
}
#endif // !_AOI_PLAYER_H__
