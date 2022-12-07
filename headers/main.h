#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.142

typedef struct vector
{
	float x;
	float y;
} Vector;

extern int map[];
extern bool running;
extern int width;
extern int height;
extern int mapW;
extern int mapH;
extern int width2d;
extern int boxSize;
extern float pA;
extern Vector pPos;
extern Vector pd;
extern Vector mapStart;
extern SDL_Window *window;
extern SDL_Renderer *renderer;

void drawMap(void);
void drawPlayer(void);
void drawIntersections(void);
void movePlayer(const Uint8 *keyStates);
bool hitsWall(Vector pt);
float castRay(Vector rd);
void initsdl(void);
void handleEvents(void);
void clearScreen(void);
void drawScreen(void);
void quitsdl(void);

#endif
