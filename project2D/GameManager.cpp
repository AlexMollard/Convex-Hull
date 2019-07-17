#include "GameManager.h"
#include "Input.h"
#include <iostream>
#include "Font.h"
#include <vector>
#include "Point.h"
#include "Application.h"


using namespace std;

GameManager::GameManager(int totalPoints)
{
	// Create some textures for testing.
	m_font = new aie::Font("./font/consolas.ttf", 24);


	_totalPoints = totalPoints;
	_pointSize = 10.0f;
	SetPoints();
}

GameManager::~GameManager()
{
	delete m_font;
}

void GameManager::Update(float deltaTime)
{

	aie::Input* input = aie::Input::GetInstance();

	if (input->WasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		SetPoints();
	}

	if (input->WasKeyPressed(aie::INPUT_KEY_RIGHT))
	{
		findConvexHull(_point,_totalPoints);	
	}

}

void GameManager::SetPoints()
{
	aie::Application* application = aie::Application::GetInstance();

	_point.clear();
	_hull.clear();
	for (int i = 0; i < _totalPoints; i++)
	{
		_point.push_back(Point(rand() % application->GetWindowWidth() * 0.95, rand() % application->GetWindowHeight() * 0.95));
	}

	BubbleSort(_point);


	//Get Most Left
	_mostLeft = &_point[0];
	for (int i = 0; i < _totalPoints; i++)
	{
		if (_point[i].GetX() < _mostLeft->GetX())
		{
			_mostLeft = &_point[i];
		}
	}
	_lastCurrent = _mostLeft;
	_hull.push_back(*_mostLeft);
}

// a: previous point
// b: most left(current point)
// c: comparing point

int GameManager::Orientation(Point a, Point b, Point c)
{
	int y1 = a.GetY() - b.GetY();
	int y2 = a.GetY() - c.GetY();
	int x1 = a.GetX() - b.GetX();
	int x2 = a.GetX() - c.GetX();

	return y2 * x1 - y1 * x2;
}

int GameManager::Distance(Point a, Point b, Point c)
{
	int y1 = a.GetY() - b.GetY();
	int y2 = a.GetY() - c.GetY();
	int x1 = a.GetX() - b.GetX();
	int x2 = a.GetX() - c.GetX();

	int item1 =  y1 * x1 - x1 * x1;
	int item2 =  y2 * x2 - x2 * x2;

	if (item1 == item2)
		return 0;
	else if (item1 < item2)
		return -1;

	return 1;
}



void GameManager::findConvexHull(std::vector <Point> points, int n) {
		Point start = points[0];
		for (int i = 1; i < n; i++) {    //find the left most point for starting
			if (points[i].GetX() < start.GetX())
				start = points[i];
		}

		while (true)
		{
			_Current = &start;
			std::vector<Point> _UsedPoints;
			_UsedPoints.clear();
			for (int i = 0; i < _point.size(); i++)
			{
				if (&_point[i] == _Current)
					continue;

				int val = Orientation(*_lastCurrent, *_Current, _point[i]);

				if (val > 0)
				{
					_lastCurrent = &_point[i];
				}
				else if (val == 0)
				{
					if (Distance(*_lastCurrent, *_Current, _point[i]) < 0)
					{
						_UsedPoints.push_back(*_Current);
						_Current = &_point[i];
					}
					else
					{
						_UsedPoints.push_back(_point[i]);
					}
				}
			}

			std::vector<Point>::iterator it;

			//for (it == _UsedPoints.begin(); it != _UsedPoints.end(); it++)
			//{
			//	_hull.insert(*it);
			//}

			//if (_Current == _mostLeft)
				break;

			//_hull.push_back(_Current);
			//_Current = _lastCurrent;
		}
		//return _hull;
	}

void GameManager::Swap(Point* a, Point* b)
{
	Point temp = *a;
	*a = *b;
	*b = temp;
}

void GameManager::BubbleSort(std::vector<Point>& a)
{
	bool swapp = true;
	while (swapp)
	{
		swapp = false;

		for (int j = 0; j < a.size(); j++)
		{
			for (int i = 0; i < a.size() - 1; i++)
			{
				if (a[i].GetX() > a[i + 1].GetX())
				{
					Swap(&a[i], &a[i + 1]);
				}
			}

		}
	}
}

void GameManager::Draw(aie::Renderer2D* renderer)
{
	for (int i = 0; i < _point.size(); i++)
	{
		Point _tempPoint = _point[i];
		float _posX = _tempPoint.GetX();
		float _posY = _tempPoint.GetY();
		

		renderer->SetRenderColour(1.0f, 1.0f, 1.0f);

		renderer->DrawCircle(_posX, _posY, _pointSize);
	}
	

	for (int i = 0; i < _hull.size(); i++)
	{
		renderer->SetRenderColour(1.0f, 0.0f, 1.0f);

		renderer->DrawCircle(_hull[i].GetX(), _hull[i].GetY(), _pointSize * 1.5f);

		if (_hull.size() > 1 && i != 0)
		{
			renderer->DrawLine(_hull[i - 1].GetX(), _hull[i - 1].GetY(), _hull[i].GetX(), _hull[i].GetY(), 5.0f);
		}
	}



	renderer->SetRenderColour(0.0f, 1.0f, 0.0f);

	renderer->DrawCircle(_point[0].GetX(), _point[0].GetY(), _pointSize * 2.5f);

	renderer->SetRenderColour(1.0f, 0.0f, 0.0f);

	renderer->DrawCircle(_point.back().GetX(), _point.back().GetY(), _pointSize * 2.5f);

}