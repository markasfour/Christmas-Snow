#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

//screen dimensions
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//the window to render to 
SDL_Window *WINDOW = NULL;
	
//the window renderer
SDL_Renderer *RENDERER = NULL;

//the surface contained by the window
SDL_Surface *SCREENSURFACE = NULL;

//Current displayed image
SDL_Surface *BACKGROUND = NULL;

#endif
