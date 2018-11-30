#pragma once
#ifndef _MYAOI_DEFINES_H__
#define _MYAOI_DEFINES_H__

#include <cmath>
#include <limits>

enum EPolyAreas
{
	POLYAREA_GROUND,
	POLYAREA_WATER, // 水
	POLYAREA_ROAD, // 路
	POLYAREA_DOOR, // 门窗
	POLYAREA_GRASS, // 草
	POLYAREA_JUMP // 跳跃，楼梯
};

enum EPolyFlags
{
	POLYFLAGS_WALK = 0x01, // grand road grass
	POLYFLAGS_SWIM = 0x02, // water
	POLYFLAGS_DOOR = 0x04, // door
	POLYFLAGS_JUMP = 0x08, // jump
	POLYFLAGS_DISABLED = 0x10, // disable
	POLYFLAGS_ALL = 0xffff // all abilities
};

enum {
	HEIGHT_MODE_1 = 1,   // 原始的，精度不是很高，但是没多余消耗。可以通过使Tile Size变小来提高精度
	HEIGHT_MODE_2 = 2,  // 通过公共的StaticScene上，获取精确高度值。
};


const unsigned MAX_POLYS = 4096;
const unsigned MAX_SMOOTH = 65535;
const float DEFAULT_HALF_EXTENTS[3] = { 2.0f,4.0f,2.0f };

// 判断两个浮点数是否相等
inline bool equalFloat(float a, float b)
{
	return fabs(a - b) <= std::numeric_limits<float>::epsilon();
}

// 玩家视野范围，用于广播，不考虑高度 y
const float AGENT_VIEW_WIDTH = 200.0f; // x轴
const float AGENT_VIEW_HEIGHT = 200.0f; // z轴


// 玩家 场景内事件类型
enum EAGENT_MOVE_EVENT_TYPE
{
	EAMET_ENTER_SCENE = 1,
	EAMET_LEAVE_SCENE,
	EAMET_MOVE_SCENE
};
// 怪物 场景内事件类型
enum EMONSTER_EVENT_TYPE
{
	EMET_MOVE_SCENE = 1,
	EMET_DEAD_SCENE
};



#endif // !_MYAOI_DEFINES_H__

