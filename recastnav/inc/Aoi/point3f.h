#pragma once
#ifndef _MYAOI_POINT3F_H__
#define _MYAOI_POINT3F_H__

#include "Aoi/defines.h"
#include <ostream>
#include <iostream>

namespace aoi
{
	class Point3f
	{
	public:
		float x, y, z;

		Point3f(float  X, float  Y,float Z);
		Point3f() :
			x(0.0f),
			y(0.0f),
			z(0.0f)
		{
		}
		Point3f(const Point3f& other) :
			x(other.x),
			y(other.y),
			z(other.z)
		{
		}

		Point3f& operator=(const Point3f& other)
		{
			x = (other.x);
			y = (other.y);
			z = (other.z);
			return *this;
		}

		void Reset(float _x, float _y, float _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}

		bool IsZero()
		{
			return equalFloat(x,0) && equalFloat(y, 0) && equalFloat(z, 0);
		}

		bool operator == (const Point3f &other) const;
		bool operator != (const Point3f &other) const;
	};

	std::ostream& operator << (std::ostream &output, const Point3f &p);
}
#endif // !_MYAOI_POINT3F_H__

