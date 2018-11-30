#pragma once
#ifndef _AOI_OBJECT1_H__
#define _AOI_OBJECT1_H__

#include <iostream>

namespace aoi
{
	template<typename OBJ_ID_TYPE>
	class Object1
	{
	public:
		Object1(OBJ_ID_TYPE id) : m_position(), m_id(id) {}
		virtual ~Object1() {
			//std::cout << "objec1 destructor" << std::endl;
		}
	public:
		inline const Point3f GetPosition() const { return m_position; }
		inline void SetPosition(Point3f& pos) { m_position = pos; }
		inline void SetPosition(float x, float y, float z) { m_position.Reset(x, y, z); }
		inline const OBJ_ID_TYPE GetId() const { return m_id; }
	private:
		Point3f m_position;
		OBJ_ID_TYPE m_id;
	};
}
#endif // !_AOI_OBJECT1_H__
