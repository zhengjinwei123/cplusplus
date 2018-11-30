#pragma once
#ifndef _MYAOI_AABB_H__
#define _MYAOI_AABB_H__

#include "Aoi/point3f.h"
#include "Aoi/vec3f.h"

namespace aoi
{
	class AABB
	{
	public:
		Vec3f m_center; // 包围盒中点
		Vec3f m_halfDims; // 包围盒尺寸的一半

	public:
		Vec3f m_lowerBound; // 小边界
		Vec3f m_upperBound;// 大边界

		void CalculateHalfDims();
		void CalculateCenter();
		void CalculateBounds();

		AABB();
		AABB(const Vec3f& lowerBound, const Vec3f &upperBound);
		AABB(float x, float z, float w, float h);
		AABB(float w, float h);

		const Vec3f &GetCenter() const;
		Vec3f GetDims() const;

		const Vec3f& GetHalfDims() const;
		const Vec3f& GetLowerBound() const;
		const Vec3f& GetUpperBound()  const;

		inline float GetWidth() {
			return m_upperBound.x - m_lowerBound.x;
		}

		inline float GetHeight() {
			return m_upperBound.z - m_lowerBound.z;
		}


		inline void Set(Point3f& pos)
		{
			Set(pos.x, pos.y, pos.z);
		}
		inline void Set(float x,float y,float z)
		{
			float w = GetWidth();
			float h = GetHeight();

			m_lowerBound.Set(x - w / 2, y, z - h / 2);
			m_upperBound.Set(x + w / 2, y, z + h / 2);

			CalculateHalfDims();
			CalculateCenter();
		}

		inline float GetX()
		{
			return m_center.x;
		}
		inline float GetY()
		{
			return m_center.y;
		}
		inline float GetZ()
		{
			return m_center.z;
		}

		AABB GetRotatedAABB(float angleRads) const;

		// Modifiers
		void SetLowerBound(const Vec3f &newLowerBound) {
			m_lowerBound.x = newLowerBound.x;
			m_lowerBound.y = newLowerBound.y;
			m_lowerBound.z = newLowerBound.z;

			CalculateHalfDims();
			CalculateCenter();
		}
		void SetUpperBound(const Vec3f &newUpperBound)
		{
			m_upperBound.x = newUpperBound.x;
			m_upperBound.y = newUpperBound.y;
			m_upperBound.z = newUpperBound.z;

			CalculateHalfDims();
			CalculateCenter();
		}
		void SetCenter(const Vec3f &newCenter);
		void IncCenter(const Vec3f &increment);

		void SetDims(const Vec3f &newDims);

		void SetHalfDims(const Vec3f &newDims);

		void SetRotatedAABB(float angleRads);

		// Utility
		bool Intersects(const AABB &other) const;
		bool Contains(const AABB &other) const;
	};
}
#endif // _MYAOI_AABB_H__
