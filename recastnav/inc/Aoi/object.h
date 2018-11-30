#pragma once
#ifndef _MYAOI_OBJECT_H__
#define  _MYAOI_OBJECT_H__

#include "Aoi/aabb.h"
#include "Aoi/quadTree.h"
#include "Aoi/point3f.h"


namespace aoi {
	class Object 
	{
	public:
		friend class QuadTree;
	public:
		AABB& GetBound()
		{
			return m_bound;
		}
	public:
		Object::Object(AABB& bound, int id) :
			m_bound(bound),
			m_quadtreePtr(nullptr)
		{

		}

		Object(const Object& other) :
			m_bound(other.m_bound),
			m_quadtreePtr(other.m_quadtreePtr)
		{

		}
		virtual ~Object()
		{

		}

		inline void Set(Point3f& pos)
		{
			m_bound.Set(pos);
		}

		inline float GetX()  { return m_bound.GetX(); }
		inline float GetY() { return m_bound.GetY(); }
		inline float GetZ() { return m_bound.GetZ(); }

		inline float GetWidth() { return m_bound.GetWidth(); }
		inline float GetHeight() { return m_bound.GetHeight(); }

		bool Intersects(const AABB &other) const
		{
			return m_bound.Intersects(other);
		}
		bool Contains(const AABB &other) const
		{
			return m_bound.Contains(other);
		}
		
	protected:
		AABB m_bound;
		QuadTree* m_quadtreePtr;
	};
}

#endif // !_MYAOI_OBJECT_H__
