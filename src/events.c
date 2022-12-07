#include "../headers/main.h"

void movePlayer(const Uint8 *keyStates)
{
	Vector nextpos = pPos;
	if (keyStates[SDL_SCANCODE_W])
	{
		if (pd.y < 0)
			nextpos.y -= 10;
		else
			nextpos.y += 10;
		if (!hitsWall(nextpos))
			pPos.y += pd.y * 1.2;
		nextpos = pPos;
		if (pd.x < 0)
			nextpos.x -= 10;
		else
			nextpos.x += 10;
		if (!hitsWall(nextpos))
			pPos.x += pd.x * 1.2;
	}
	if (keyStates[SDL_SCANCODE_S])
	{
		if (pd.y < 0)
			nextpos.y += 10;
		else
			nextpos.y -= 10;
		if (!hitsWall(nextpos))
			pPos.y -= pd.y * 1.2;
		nextpos = pPos;
		if (pd.x < 0)
			nextpos.x += 10;
		else
			nextpos.x -= 10;
		if (!hitsWall(nextpos))
			pPos.x -= pd.x * 1.2;
	}
	if (keyStates[SDL_SCANCODE_A])
	{
		pA -= 0.03;
		if (pA <= PI * 2)
			pA += PI * 2;
	}
	if (keyStates[SDL_SCANCODE_D])
	{
		pA += 0.03;
		if (pA > PI * 2)
			pA -= PI * 2;
	}
}
