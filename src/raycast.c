#include "../headers/main.h"

bool hitsWall(Vector pt)
{
	Vector p;
	p.x = ((int)pt.x / boxSize) * boxSize;
	p.y = ((int)pt.y / boxSize) * boxSize;
	int i = p.y / boxSize * mapW + p.x / boxSize;
	if (map[i] == 1)
		return (1);
	return (0);
}
float castRay(Vector rd)
{
	Vector unitlength, raylength, dir, lasttile;
	float distance;
	bool hit;
	int mapindex;
	unitlength.x = sqrt(1 + (rd.y / rd.x) * (rd.y / rd.x));
	unitlength.y = sqrt(1 + (rd.x / rd.y) * (rd.x / rd.y));
	lasttile.x = ((int)pPos.x / boxSize) * boxSize;
	lasttile.y = ((int)pPos.y / boxSize) * boxSize;
	if (rd.x < 0)
	{
		dir.x = -1;
		raylength.x = (pPos.x - lasttile.x) * unitlength.x;
	}
	else
	{
		dir.x =  1;
		raylength.x = (lasttile.x + boxSize - pPos.x) * unitlength.x;
	}
	if (rd.y < 0)
	{
		dir.y = -1;
		raylength.y = (pPos.y - lasttile.y) * unitlength.y;
	}
	else
	{
		dir.y =  1;
		raylength.y = (lasttile.y + boxSize - pPos.y) * unitlength.y;
	}
	distance = 0;
	hit = 0;
	mapindex = 0;
	char wall;
	while (!hit && distance < 800)
	{
		if (raylength.x < raylength.y)
		{
			lasttile.x += dir.x * boxSize;
			distance = raylength.x;
			raylength.x += unitlength.x * boxSize;
			wall = 'h';
		}
		else
		{
			lasttile.y += dir.y * boxSize;
			distance = raylength.y;
			raylength.y += unitlength.y * boxSize;
			wall = 'v';
		}
		if (lasttile.x >= 0 && lasttile.x < width2d && lasttile.y >= 0 && lasttile.y < height)
		{
			if (hitsWall(lasttile))
				hit = 1;
		}
	}
	if (wall == 'h')
		SDL_SetRenderDrawColor(renderer, 150, 80, 0, 255);
	else
		SDL_SetRenderDrawColor(renderer, 200, 110, 0, 255);
	return (distance);
}
