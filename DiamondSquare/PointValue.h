#pragma once
#ifndef  __POINTVALUE_H_
#define __POINTVALUE_H_
#include "Point.h"

class PointValue : public Point{
private:
	float value;
public:
	PointValue() : Point() { value = 0; }
	PointValue(int _x, int _y, float val) : Point(_x, _y) { value = val; }
	~PointValue();

	void setValue(float _val) { value = _val; }
	float getValue() { return value; }
};

#endif // ! __POINTVALUE_H_

