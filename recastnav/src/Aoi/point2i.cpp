#include "Aoi/point2i.h"

namespace aoi
{
	Point2i::Point2i()
	{
	}

	Point2i::Point2i(int X, int Y)
		: x(X), y(Y)
	{
	}

	bool Point2i::operator==(const Point2i &other) const
	{
		if (x == other.x && y == other.y)
			return true;

		return false;
	}

	bool Point2i::operator!=(const Point2i &other) const
	{
		if (x != other.x || y != other.y)
			return true;

		return false;
	}
}