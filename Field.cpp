#include "stdafx.h"
#include "Field.h"


Field::Field(int width, int height) {
	this->height = height;
	this->width = width;
	arr = new bool[height*width]{false};
}

bool Field::turnPixelOn(int x, int y) {
	if (x >= width || y >= height) {
		return false;
	}
	arr[width*y + x] = true;
	return true;
}

bool Field::turnPixelOff(int x, int y) {
	if (x >= width || y >= height) {
		return false;
	}
	arr[width*y + x] = false;
	return true;
}

bool Field::togglePixel(int x, int y) {
	if (x >= width || y >= height) {
		return false;
	}
	arr[width*y + x] = !arr[width*y + x];
	return true;
}

bool* Field::getField() {
	return arr;
}

int Field::getHeight() {
	return height;
}

int Field::getWidth() {
	return width;
}