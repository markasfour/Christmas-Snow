#ifndef FLAKE_H
#define FLAKE_H

#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

struct flake
{
	SDL_Rect R;
	Uint8 r = 0xFF;
	Uint8 g = 0xFF;
	Uint8 b = 0xFF;
	Uint8 a = 0xFF;
	int v_x = 0;
	int v_y = 0;
	bool Front = false;
	bool Middle = false;
	bool Back = false;

	flake()
	{
		R.x = 0;
		R.y = 0;
		R.w = 5;
		R.h = 5;
		Front = true;
	}

	flake(int SCREEN_WIDTH)
	{
		R.x = rand() % SCREEN_WIDTH;
		R.y = 0;
		R.w = 5;
		R.h = 5;
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

	int jitter()
	{
		return rand() % 3-3/2;
	}

	void move()
	{
		R.x += v_x + jitter();
		if (abs(v_x) > 0)
		{
			if (v_x > 0)
				v_x--;
			else if (v_x < 0)
				v_x++;
		}

		R.y += 1 + v_y + jitter();
		if (abs(v_y) > 0)
		{
			if (v_y > 0)
				v_y--;
			else if (v_y < 0)
				v_y++;
		}
	}
	
	void on_click(int mouse_x, int mouse_y)
	{
		int dx = mouse_x - R.x;
		int dy = mouse_y - R.y;
		if ((abs(dx) * abs(dx)) + (abs(dy) * abs(dy)) <= (100 * 100))
		{
			if (dx > 0) //flake left of mouse
			{
				R.x--;
				v_x -= (100/dx)/2;
			}
			else if (dx < 0) //flake right of mouse
			{	
				R.x++;
				v_x += -1 * (100/dx)/2;
			}
			if (dy > 0) //flake above mouse
			{	
				R.y--;
				v_y -= (100/dy)/2;
			}
			else if (dy < 0) //flake below mouse
			{	
				R.y++;
				v_y += -1 * (100/dy)/2;
			}
		}
	}

};

#endif
