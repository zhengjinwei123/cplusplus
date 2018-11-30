#pragma once
#ifndef _MYAOI_VEC3F_H__
#define  _MYAOI_VEC3F_H__

#include <iostream>

namespace aoi
{
	class Vec3f
	{
	public:
		float x, y,z;

		Vec3f();
		Vec3f(float X, float Y,float Z);
		void Set(float X,float Y,float Z);
		bool operator == (const Vec3f &other) const;

		Vec3f operator*(float scale) const;
		Vec3f operator/(float scale) const;
		Vec3f operator+(const Vec3f& other) const;
		Vec3f operator-(const Vec3f& other) const;
		Vec3f operator-() const;

		const Vec3f &operator *= (float scale);
		const Vec3f &operator/=(float scale);
		const Vec3f &operator+=(const Vec3f &other);
		const Vec3f &operator-=(const Vec3f &other);

		float Magnitude() const;
		float MagnitudeSquared() const;
		Vec3f Normalize() const;
		float Dot(const Vec3f &other) const;
		float Cross(const Vec3f &other) const;


	};

	Vec3f operator*(float scale, const Vec3f &v);
	std::ostream &operator<<(std::ostream &output, const Vec3f &v);
}

#endif // !_MYAOI_VEC3F_H__
