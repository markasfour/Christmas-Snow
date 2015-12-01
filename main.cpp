#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main()
{
	//the window to render to 
	SDL_Window *window = NULL;
	
	//the surface contained by the window
	SDL_Surface *screenSurface = NULL;

	//init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL failed to initialize. SDL_Error: " << SDL_GetError() << endl;
	}
	else
	{
		//create window
		window = SDL_CreateWindow( "Christmas Snow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			cout << "Window could not be created. SDL_Error: " << SDL_GetError() << endl;
		}
		else
		{
			//get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			//update the surface
			SDL_UpdateWindowSurface(window);

			//wait
			SDL_Delay(2000);
		}
	}

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL
	SDL_Quit();

	return 0;
}
