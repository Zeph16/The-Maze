#include "../headers/main.h"
#include <SDL2/SDL_video.h>

SDL_Renderer *renderer;
SDL_Window *window;

void initsdl(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("SDL Experiment", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void handleEvents(void)
{	SDL_Event event;
	const Uint8 *keyStates = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			running = false;
	}
	movePlayer(keyStates);
}

void clearScreen(void)
{
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderClear(renderer);
}

void drawScreen(void)
{
	SDL_RenderPresent(renderer);
}

void quitsdl(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
