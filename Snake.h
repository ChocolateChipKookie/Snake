#pragma once
#include "Field.h"
#include <list>

enum Direction{RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3};

typedef struct Point {
	int x, y;
};

class Snake :
	public Field
{
public:
	Snake(int width, int height, int startingX, int startingY);
	void updateDirection(Direction direction);
	void updateSnake();
	Point getFoodPosition();
	bool gameRunning = true;
	
private:

	void getFoodPosition(int* x, int *y);

	bool canUpdateDirection = true;

	std::list<Point> pointList;
	Direction direction;
	Point headPosition;
	Point food;
};

