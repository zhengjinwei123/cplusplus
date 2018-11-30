#pragma once
#ifndef _MYAOI_FILTER_H__
#define _MYAOI_FILTER_H__

#include "Aoi/defines.h"
#include <memory>

class dtQueryFilter;

namespace aoi {
	
	const float DEFAULT_AREA_COST_GROUND = 1.0f;
	const float DEFAULT_AREA_COST_WATER = 10.0f;
	const float DEFAULT_AREA_COST_ROAD = 1.0f;
	const float DEFAULT_AREA_COST_DOOR = 1.0f;
	const float DEFAULT_AREA_COST_GRASS = 2.0f;
	const float DEFAULT_AREA_COST_JUMP = 1.5f;


	const unsigned short DEFAULT_INCLUDE_FLAGS = POLYFLAGS_ALL ^ POLYFLAGS_DISABLED;
	const unsigned short DEFAULT_EXCLUDE_FLAGS = 0;

	class Filter {
	public:
		Filter();
		virtual ~Filter();

		dtQueryFilter& Get() { return *mFilter; }
		void SetAreaCost(const int i, const float cost);
		void SetIncludeFlags(const unsigned short flags);
		void SetExcludeFlags(const unsigned short flags);

	protected:
		std::unique_ptr<dtQueryFilter> mFilter;
	};
};

#endif // !_MYAOI_FILTER_H__
