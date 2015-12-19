#ifndef FLAKE_H
#define FLAKE_H

#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;

struct flake
{
	SDL_Rect R = {0, 0, 3, 3};
	Uint8 r = 0xFF;
	Uint8 g = 0xFF;
	Uint8 b = 0xFF;
	Uint8 a = 0xFF;
	double v_x = 0;
	double v_y = 0;
	bool Front = false;
	bool Middle = false;
	bool Back = false;

	flake()	{}

	flake(int SCREEN_WIDTH, int location)
	{
		R.x = rand() % SCREEN_WIDTH;
		
		if (location == 0)
			Front = true;
		else if (location == 1)
			Middle = true;
		else if (location == 2)
			Back = true;
		if (Front)
		{
			r = 0xFF, g = 0xFF, b = 0xFF, a = 0xFF;
			R.w = 4, R.h = 4;
		}
		else if (Middle)
		{	
			r = 0xDF, g = 0xDF, b = 0xDF, a = 0xFF;
		}
		else if (Back)
		{
			r = 0xBF, g = 0xBF, b = 0xBF, a = 0xFF;
			R.w = 2, R.h = 2;
		}
	}

	int jitter()
	{
		return rand() % 3-3/2;
	}

	void move()
	{
		double level = 1;
		if (Middle)
			level /= 2;
		if (Back)
			level /= 3;

		R.x += (double(v_x) * level) + jitter();
		if (abs(v_x) > 0)
		{
			if (v_x > 0)
				v_x -= (1.0 / level);
			else if (v_x < 0)
				v_x += (1.0 / level);
		}

		R.y += 1 + (double(v_y) * level) + jitter();
		if (abs(v_y) > 0)
		{
			if (v_y > 0)
				v_y -= (1.0 / level);
			else if (v_y < 0)
				v_y += (1.0 / level);
		}
	}
	
	void on_click(int mouse_x, int mouse_y)
	{
		double level = 1;
		if (Middle)
			level /= 2;
		if (Back)
			level /= 3;
		
		int dx = mouse_x - R.x;
		int dy = mouse_y - R.y;
		if ((abs(dx) * abs(dx)) + (abs(dy) * abs(dy)) <= (100 * 100 * level))
		{
			if (dx > 0) //flake left of mouse
			{
				R.x -= 5 * level;
				v_x -= (100/dx)/2 * level;
			}
			else if (dx < 0) //flake right of mouse
			{	
				R.x += 5 * level;
				v_x += -1 * (100/dx)/2 * level;
			}
			if (dy > 0) //flake above mouse
			{	
				R.y -= 5 * level;
				v_y -= (100/dy)/2 * level;
			}
			else if (dy < 0) //flake below mouse
			{	
				R.y -= 5 * level;
				v_y += -1 * (100/dy)/2 * level;
			}
		}
	}

};

#endif
