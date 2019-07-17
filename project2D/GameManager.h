#pragma once
#include "Renderer2D.h"
#include "Point.h"
#include <vector>
#include <set>

class GameManager
{
public:
	GameManager(int totalpoints);
	~GameManager();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);
	void SetPoints();
	int Orientation(Point a, Point b, Point c);
	int Distance(Point a, Point b, Point c);
	void findConvexHull(std::vector <Point> points, int n);
	void Swap(Point *a, Point *b);
	void BubbleSort(std::vector<Point>& a);
private:
	int _totalPoints;
	float _pointSize;
	std::vector<Point> _point;
	std::vector<Point> _hull;
	Point* _mostLeft;
	Point* _lastCurrent;
	aie::Font* m_font;
	Point* _Current;
};

