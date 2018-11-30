#include "Aoi/vec3f.h"
#include "Aoi/defines.h"

#include <cmath>

namespace aoi
{
	Vec3f::Vec3f()
	{

	}

	Vec3f::Vec3f(float X, float Y,float Z) :
		x(X),
		y(Y),
		z(Z)
	{

	}

	void Vec3f::Set(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	bool Vec3f::operator == (const Vec3f &other) const {
		if (equalFloat(x,other.x) && equalFloat(y,other.y) && equalFloat(z,other.z))
		{
			return true;
		}
		return false;
	}

	Vec3f Vec3f::operator*(float scale) const
	{
		return Vec3f(x * scale, y * scale,z*scale);
	}

	Vec3f Vec3f::operator/(float scale) const
	{
		return Vec3f(x / scale, y / scale,z / scale);
	}


	Vec3f Vec3f::operator+(const Vec3f &other) const
	{
		return Vec3f(x + other.x, y + other.y,z + other.z);
	}

	Vec3f Vec3f::operator-(const Vec3f &other) const
	{
		return Vec3f(x - other.x, y - other.y,z - other.z);
	}

	Vec3f Vec3f::operator-() const
	{
		return Vec3f(-x, -y,-z);
	}

	const Vec3f &Vec3f::operator*=(float scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;

		return *this;
	}

	const Vec3f &Vec3f::operator/=(float scale)
	{
		x /= scale;
		y /= scale;
		z /= scale;

		return *this;
	}

	const Vec3f &Vec3f::operator+=(const Vec3f &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	const Vec3f &Vec3f::operator-=(const Vec3f &other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	float Vec3f::Magnitude() const
	{
		return std::sqrt(x * x + y * y+ z*z);
	}

	float Vec3f::MagnitudeSquared() const
	{
		return x * x + y * y + z*z;
	}

	Vec3f Vec3f::Normalize() const
	{
		float m = std::sqrt(x * x + y * y+z*z);
		return Vec3f(x / m, y / m,z / m);
	}

	float Vec3f::Dot(const Vec3f &other) const
	{
		return x * other.x + y * other.y+ z * other.z;
	}

	float Vec3f::Cross(const Vec3f &other) const
	{
		return x * other.y - y * other.x - z*other.z;
	}

	Vec3f operator*(float scale, const Vec3f &v)
	{
		return v * scale;
	}

	std::ostream &operator<<(std::ostream &output, const Vec3f &v)
	{
		output << '(' << v.x << ", " << v.y << "," << v.z <<')';
		return output;
	}

}