#pragma once
class Point
{
public:
	Point(float x, float y);
	~Point();

	float GetX();
	float GetY();
	void SetPos(float x, float y);

	bool _Used;
private:
	float x;
	float y;
};

