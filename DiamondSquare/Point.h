#pragma once
#ifndef __POINT_H_
#define __POINT_H_

class Point {
private:
	int x;
	int y;

public:
	Point();
	Point(int _x, int _y);
	
	virtual int getX() const;
	virtual int getY() const;
	
	virtual void setX(int _x) { x = _x; }
	virtual void setY(int _y) { y = _y; }

	Point findMidPoint(const Point otherPoint); //mostly used for the DiamondSquare Algorithm initially
	
	bool operator==(const Point& point) {
		if (x == point.getX() && y == point.getY()) {
			return true;
		}
		return false;
	}
};

#endif // !__POINT_H_
