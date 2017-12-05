#include "stdafx.h"
#include "Snake.h"
#include <list>
#include <cstdlib>
#include <ctime>

Snake::Snake(int width, int height, int startingX, int startingY)
	:Field(width, height), headPosition({ startingX, startingY })
{
	pointList.push_back(headPosition);
	srand((unsigned int)time(NULL));

	getFoodPosition(&(food.x), &(food.y));
}

void Snake::getFoodPosition(int* x, int *y) {
	int j = rand() % (width*height - ((int)pointList.size()));
	for (int i = 0; i < j; i++) {
		if (arr[i]) {
			j++;
		}
	}

	*x = j % width;
	*y = j / width;
}

void Snake::updateDirection(Direction direction)
{
	if ((this->direction) == direction || ((this->direction) + 2) % 4 == direction || !canUpdateDirection) {
		return;
	}
	this->direction = direction;
	canUpdateDirection = false;
}

void Snake::updateSnake()
{
	int x = headPosition.x;
	int y = headPosition.y;
	
	switch (direction) {
	case RIGHT:
		x++;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	case UP:
		y--;
	}

	if (x < 0 || x >= width || y < 0 || y >= height) {
		gameRunning = false;
	}

	if (x == food.x && y == food.y) {
		turnPixelOn(x, y);
		headPosition = { x, y };
		pointList.push_back(headPosition);

		getFoodPosition(&(food.x), &(food.y));
	}
	else{
		Point tail = pointList.front();
		turnPixelOff(tail.x, tail.y);
		pointList.pop_front();

		if (arr[y*width + x]) {
			gameRunning = false;
		}

		turnPixelOn(x, y);
		headPosition = { x, y };
		pointList.push_back(headPosition);
	}

	canUpdateDirection = true;
}

Point Snake::getFoodPosition() {
	return food;
}
