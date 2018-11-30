#pragma once
#ifndef _MYAOI_POINT2I_H__
#define _MYAOI_POINT2I_H__

namespace aoi
{
	class Point2i
	{
	public:
		int x, y;

		Point2i(int X, int Y);
		Point2i();

		bool operator == (const Point2i &other) const;
		bool operator != (const Point2i &other) const;
	};
}

#endif // !_MYAOI_POINT2I_H__
