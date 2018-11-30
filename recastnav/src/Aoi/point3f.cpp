#include "Aoi/point3f.h"

namespace aoi
{
	Point3f::Point3f(float X, float Y,float Z) :
		x(X),
		y(Y),
		z(Z)
	{
	}

	bool Point3f::operator==(const Point3f &other) const
	{
		if (equalFloat(x,other.x) && equalFloat(y,other.y) && equalFloat(z,other.z))
			return true;

		return false;
	}

	bool Point3f::operator!=(const Point3f &other) const
	{
		if (!equalFloat(x,other.x) || !equalFloat(y, other.y) && !equalFloat(z,other.z))
			return true;

		return false;
	}

	std::ostream& operator << (std::ostream &output, const Point3f &p)
	{
		output << "(" << p.x << "," << p.y << "," << p.z << ")" << std::endl;
		return output;
	}
}