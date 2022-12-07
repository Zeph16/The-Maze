#include "../headers/main.h"

int width = 1460;
int width2d = 720;
int height = 720;
int mapW = 15;
int mapH = 15;
int boxSize = 32;
bool running;

Vector pPos = {70, 70};
float pA = PI / 2;
Vector pd = {0, 0};
int main(int argc, char **argv)
{
	initsdl();
	running = true;
	while (running)
	{
		handleEvents();
		pd.x = cos(pA);
		pd.y = sin(pA);
		clearScreen();
		drawMap();
		drawPlayer();
		drawIntersections();
		drawScreen();
	}
	quitsdl();
	return (0);
}
