#include "stdafx.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "Field.h"
#include "FieldDisplay.h"
#include "Snake.h"

int main(int argc, char *argv[]) {
	//#[Kookie]

	int arrayHeight = 20;
	int arrayWidth = 20;
	int pixelSize = 30;

	int waitCyclesDefault = 20;
	int waitCycles = 0;

	int delay = 10;

	int HEIGHT = arrayHeight*pixelSize;
	int WIDTH = arrayWidth*pixelSize;

	SDL_Rect windowSize = { HEIGHT, WIDTH, 0, 0 };

	//Initialise the variables for the loop
	bool isRunning = true;
	SDL_Event ev;

	SDL_Surface *textSurface = NULL;
	SDL_Texture *text = NULL;

	SDL_Window *window;
	SDL_Renderer *renderTarget;
	SDL_Texture *targetTexure;

	SDL_Color background{ 255, 255, 255, 255 };
	SDL_Color foodColor{ 255, 0, 0, SDL_ALPHA_OPAQUE };

	srand((unsigned int)time(NULL));

	//Initialise all the things needed for SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error 1:" << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}
	else {
		window = SDL_CreateWindow("GravitySimulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
		if (!window) {
			std::cout << "Error 2:" << SDL_GetError() << std::endl;
		}

		renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (!renderTarget) {
			std::cout << "Error 4:" << SDL_GetError() << std::endl;
		}

		targetTexure = SDL_CreateTexture(renderTarget, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);

		SDL_SetRenderDrawColor(renderTarget, background.r, background.g, background.b, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderTarget);
	}

	Snake snake(arrayWidth, arrayHeight, arrayWidth/2-1, arrayHeight / 2 - 1);

	FieldDisplay fieldDisplay(snake.getField(), arrayHeight, arrayWidth, pixelSize, renderTarget);
	
	//Game loop
	while (snake.gameRunning) {
		//USED TO FETCH COMMANDS
		if (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT) {
				snake.gameRunning = false;
			}
			else if (ev.type == SDL_KEYDOWN) {
				if (ev.key.keysym.sym == SDLK_RIGHT) {
					snake.updateDirection(RIGHT);
				}
				if (ev.key.keysym.sym == SDLK_LEFT) {
					snake.updateDirection(LEFT);
				}
				if (ev.key.keysym.sym == SDLK_DOWN) {
					snake.updateDirection(DOWN);
				}
				if (ev.key.keysym.sym == SDLK_UP) {
					snake.updateDirection(UP);
				}
			}
		}

		if (waitCycles <= 0) {
			snake.updateSnake();
			fieldDisplay.updateRenderTarget();
			fieldDisplay.displayFood(foodColor, snake.getFoodPosition());
			waitCycles = waitCyclesDefault;

			//DISPLAYS THE PRESENT RENDER TARGET, AND DELAYS THE OPERATION
			SDL_RenderPresent(renderTarget);
		}
		else waitCycles--;
		
		SDL_Delay(delay);
	}

	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyWindow(window);

	text = NULL;
	textSurface = NULL;
	renderTarget = NULL;
	window = NULL;

	SDL_Quit();
	IMG_Quit();
	return EXIT_SUCCESS;
	//#[/Kookie]
}
