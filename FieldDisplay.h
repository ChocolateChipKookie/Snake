#pragma once
#include "SDL.h"
#include "Snake.h"


class FieldDisplay
{
public:
	FieldDisplay(bool* arr, int height, int width, int pixelDimension, SDL_Renderer* renderTarget);
	
	void updateRenderTarget();
	void initialUpdate();
	void displayFood(SDL_Color foodColor, Point foodPosition);
	~FieldDisplay();

private:
	void drawOutline(int x, int y);
	void fillPixel(int x, int y, SDL_Color color);

	bool* arr;
	bool* previousArr;
	int height, width;
	SDL_Color black = { 0, 0, 0 , 0};
	SDL_Color white = { 255, 255, 255, 255};
	int pixelDimension;
	SDL_Renderer* renderTarget;
};

