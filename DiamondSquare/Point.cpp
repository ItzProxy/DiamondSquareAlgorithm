#include "stdafx.h"
#include "Point.h"

Point::Point()
{
	x = 0;
	y = 0;
}

Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;
}


int Point::getX() const
{
	return x;
}

int Point::getY() const
{
	return y;
}

Point Point::findMidPoint(const Point otherPoint)
{
	int xPoint = (int)(x + otherPoint.getX()) / 2;
	int yPoint = (int)(y + otherPoint.getY()) / 2;
	return Point(xPoint,yPoint);
}
