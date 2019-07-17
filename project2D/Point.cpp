#include "Point.h"

Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
	_Used = false;
}

Point::~Point()
{
}

float Point::GetX()
{
	return x;
}

float Point::GetY()
{
	return y;
}

void Point::SetPos(float x, float y)
{
	this->x = x;
	this->y = y;
}
