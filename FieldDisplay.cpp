#include "stdafx.h"
#include "FieldDisplay.h"
#include "SDL.h"


FieldDisplay::FieldDisplay(bool* arr, int height, int width, int pixelDimension, SDL_Renderer* renderTarget)
	:arr(arr), height(height), width(width), renderTarget(renderTarget), pixelDimension(pixelDimension)
{
	previousArr = new bool[width*height] {false};
	initialUpdate();
}

void FieldDisplay::initialUpdate() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			drawOutline(j, i);	
		}
	}
}

void FieldDisplay::updateRenderTarget() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (previousArr[i*width + j] != arr[i*width + j]) {
				previousArr[i*width + j] = arr[i*width + j];
				if (arr[i*width + j]) {
					fillPixel(j, i, black);
				}
				else {
					fillPixel(j, i, white);
					drawOutline(j, i);
				}
			}
		}
	}
}

void FieldDisplay::drawOutline(int x, int y) {
	SDL_SetRenderDrawColor(renderTarget, black.r, black.g, black.b, SDL_ALPHA_OPAQUE);
	SDL_Rect pixel = {x*pixelDimension, y*pixelDimension, pixelDimension, pixelDimension};
	SDL_RenderDrawRect(renderTarget, &pixel);
	SDL_SetRenderDrawColor(renderTarget, white.r, white.g, white.b, SDL_ALPHA_OPAQUE);
}

void FieldDisplay::fillPixel(int x, int y, SDL_Color color) {
	SDL_SetRenderDrawColor(renderTarget, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	SDL_Rect pixel = { x*pixelDimension, y*pixelDimension, pixelDimension, pixelDimension };
	SDL_RenderFillRect(renderTarget, &pixel);
	SDL_SetRenderDrawColor(renderTarget, white.r, white.g, white.b, SDL_ALPHA_OPAQUE);
}

void FieldDisplay::displayFood(SDL_Color foodColor, Point foodPosition) {
	fillPixel(foodPosition.x, foodPosition.y, foodColor);
	drawOutline(foodPosition.x, foodPosition.y);
}

FieldDisplay::~FieldDisplay()
{
}
