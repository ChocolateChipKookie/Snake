#pragma once
class Field
{
public:

	Field(int width, int height);
	bool turnPixelOn(int x, int y);
	bool turnPixelOff(int x, int y);
	bool togglePixel(int x, int y);
	bool* getField();
	int getHeight();
	int getWidth();

protected:

	int height, width;
	bool* arr;
};

