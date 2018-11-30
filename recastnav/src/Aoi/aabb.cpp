#include "Aoi/aabb.h"

#include <cmath>

namespace aoi
{
	AABB::AABB()
		: m_lowerBound(0.0f, 0.0f,0.0f), m_upperBound(1.0f, 1.0f,1.0f),
		m_center(0.5f, 0.5f,0.5f), m_halfDims(0.5f, 0.5f,0.5f)
	{
	}

	// 用来初始化对象
	AABB::AABB(float x, float z, float w, float h) :
		m_lowerBound(x - w / 2,0 , z - h / 2),
		m_upperBound(x + w / 2, 0,z + h / 2)
	{
		CalculateHalfDims();
		CalculateCenter();
	}

	

	// 用来初始化场景
	AABB::AABB(float w, float h) :
		m_lowerBound(0,0,0),
		m_upperBound(w,0,h)
	{
		CalculateHalfDims();
		CalculateCenter();
	}



	AABB::AABB(const Vec3f &lowerBound, const Vec3f &upperBound)
		: m_lowerBound(lowerBound), m_upperBound(upperBound)
	{
		CalculateHalfDims();
		CalculateCenter();
	}

	void AABB::CalculateHalfDims()
	{
		m_halfDims = (m_upperBound - m_lowerBound) / 2.0f;
	}

	void AABB::CalculateCenter()
	{
		m_center = m_lowerBound + m_halfDims;
	}

	void AABB::CalculateBounds()
	{
		m_lowerBound = m_center - m_halfDims;
		m_upperBound = m_center + m_halfDims;
	}

	const Vec3f &AABB::GetCenter() const
	{
		return m_center;
	}

	Vec3f AABB::GetDims() const
	{
		return m_upperBound - m_lowerBound;
	}

	const Vec3f &AABB::GetHalfDims() const
	{
		return m_halfDims;
	}

	const Vec3f &AABB::GetLowerBound() const
	{
		return m_lowerBound;
	}

	const Vec3f &AABB::GetUpperBound() const
	{
		return m_upperBound;
	}

	AABB AABB::GetRotatedAABB(float angleRads) const
	{
		// Get new dimensions
		float cosOfAngle = cosf(angleRads);
		float sinOfAngle = sinf(angleRads);

		Vec3f newHalfDims(m_halfDims.z * sinOfAngle + m_halfDims.x * cosOfAngle, m_halfDims.x * sinOfAngle + m_halfDims.z * cosOfAngle,0);

		return AABB(m_center - newHalfDims, m_center + newHalfDims);
	}

	void AABB::SetCenter(const Vec3f &newCenter)
	{
		m_center = newCenter;

		CalculateBounds();
	}

	void AABB::IncCenter(const Vec3f &increment)
	{
		m_center += increment;

		CalculateBounds();
	}

	void AABB::SetDims(const Vec3f &newDims)
	{
		SetHalfDims(newDims / 2.0f);
	}

	void AABB::SetHalfDims(const Vec3f &newDims)
	{
		m_halfDims = newDims;

		CalculateBounds();
	}

	void AABB::SetRotatedAABB(float angleRads)
	{
		float cosOfAngle = std::cos(angleRads);
		float sinOfAngle = std::sin(angleRads);

		m_halfDims.x = m_halfDims.z * sinOfAngle + m_halfDims.x * cosOfAngle;
		m_halfDims.y = m_halfDims.x * sinOfAngle + m_halfDims.z * cosOfAngle;
	}

	bool AABB::Intersects(const AABB &other) const
	{
		if (m_upperBound.x < other.m_lowerBound.x)
			return false;

		if (m_upperBound.z < other.m_lowerBound.z)
			return false;

		if (m_lowerBound.x > other.m_upperBound.x)
			return false;

		if (m_lowerBound.z > other.m_upperBound.z)
			return false;

		return true;
	}

	bool AABB::Contains(const AABB &other) const
	{
		if (other.m_lowerBound.x >= m_lowerBound.x &&
			other.m_upperBound.x <= m_upperBound.x &&
			other.m_lowerBound.z >= m_lowerBound.z &&
			other.m_upperBound.z <= m_upperBound.z)
			return true;

		return false;
	}
}