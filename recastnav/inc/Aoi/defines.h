#pragma once
#ifndef _MYAOI_DEFINES_H__
#define _MYAOI_DEFINES_H__

#include <cmath>
#include <limits>

enum EPolyAreas
{
	POLYAREA_GROUND,
	POLYAREA_WATER, // ˮ
	POLYAREA_ROAD, // ·
	POLYAREA_DOOR, // �Ŵ�
	POLYAREA_GRASS, // ��
	POLYAREA_JUMP // ��Ծ��¥��
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
	HEIGHT_MODE_1 = 1,   // ԭʼ�ģ����Ȳ��Ǻܸߣ�����û�������ġ�����ͨ��ʹTile Size��С����߾���
	HEIGHT_MODE_2 = 2,  // ͨ��������StaticScene�ϣ���ȡ��ȷ�߶�ֵ��
};


const unsigned MAX_POLYS = 4096;
const unsigned MAX_SMOOTH = 65535;
const float DEFAULT_HALF_EXTENTS[3] = { 2.0f,4.0f,2.0f };

// �ж������������Ƿ����
inline bool equalFloat(float a, float b)
{
	return fabs(a - b) <= std::numeric_limits<float>::epsilon();
}

// �����Ұ��Χ�����ڹ㲥�������Ǹ߶� y
const float AGENT_VIEW_WIDTH = 200.0f; // x��
const float AGENT_VIEW_HEIGHT = 200.0f; // z��


// ��� �������¼�����
enum EAGENT_MOVE_EVENT_TYPE
{
	EAMET_ENTER_SCENE = 1,
	EAMET_LEAVE_SCENE,
	EAMET_MOVE_SCENE
};
// ���� �������¼�����
enum EMONSTER_EVENT_TYPE
{
	EMET_MOVE_SCENE = 1,
	EMET_DEAD_SCENE
};



#endif // !_MYAOI_DEFINES_H__

