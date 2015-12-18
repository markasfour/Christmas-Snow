#ifndef FLAKE_H
#define FLAKE_H

#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

struct flake
{
	SDL_Rect R;
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
	bool Front = false;
	bool Middle = false;
	bool Back = false;
	bool atBottom = false;

	flake()
	{
		R.x = 0;
		R.y = 0;
		R.w = 10;
		R.h = 10;
		int temp = rand() % 3;
		if (temp == 0)
			Front = true;
		else if (temp == 1)
			Middle = true;
		else if (temp == 2)
			Back = true;
		if (Front)
			r = 0xFF, g = 0xFF, b = 0xFF, a = 0xFF;
		else if (Middle)
			r = 0xFF, g = 0xFF, b = 0xFF, a = 0xFF;
		else if (Back)
			r = 0xFF, g = 0xFF, b = 0xFF, a = 0xFF;
	}

	flake(int SCREEN_WIDTH)
	{
		R.x = rand() % SCREEN_WIDTH;
		R.y = 0;
		R.w = 10;
		R.h = 10;
		int temp = rand() % 3;
		if (temp == 0)
			Front = true;
		else if (temp == 1)
			Middle = true;
		else if (temp == 2)
			Back = true;
		if (Front)
			r = 0xFF, g = 0xFF, b = 0xFF, a = 0xFF;
		else if (Middle)
			r = 0xFF, g = 0xFF, b = 0xFF, a = 0xFF;
		else if (Back)
			r = 0xFF, g = 0xFF, b = 0xFF, a = 0xFF;
	}
	
	void move(int mouse_x, int mouse_y)
	{
		R.y++;
		int dx = mouse_x - R.x;
		int dy = mouse_y - R.y;
		if (abs(dx) < 100 && abs(dy) < 100)
		{
			if (dx > 0)
				R.x--;
			else if (dx < 0)
				R.x++;
			if (dy > 0)
				R.y--;
			else if (dy < 0)
				R.y++;
		}
	}


};

#endif
