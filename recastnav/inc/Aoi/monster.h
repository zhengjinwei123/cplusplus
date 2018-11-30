#pragma once
#ifndef _AOI_MONSTER_H__
#define _AOI_MONSTER_H__

#include "object1.h"

namespace aoi
{
	template<typename MONSTER_ID_TYPE>
	class Monster : Object1<MONSTER_ID_TYPE>
	{
	public:
		Monster(MONSTER_ID_TYPE id) : Object1(id) {}
		virtual ~Monster() {}
	};
}
#endif // !_AOI_MONSTER_H__
