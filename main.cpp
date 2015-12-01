#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

//screen dimensions
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//stars SDL and creates window
bool init();

//loads media
bool loadMedia();

//Frees media and shuts SDL down
void close();

//the window to render to 
SDL_Window *WINDOW = NULL;
	
//the surface contained by the window
SDL_Surface *SCREENSURFACE = NULL;

//image to load and show on screen
SDL_Surface *IMAGE = NULL;


bool init()
{
	//init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL failed to initialize. SDL_Error: " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		//create window
		WINDOW = SDL_CreateWindow( "Christmas Snow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (WINDOW == NULL)
		{
			cout << "Window could not be created. SDL_Error: " << SDL_GetError() << endl;
			return false;
		}
		else
		{
			//get window surface
			SCREENSURFACE = SDL_GetWindowSurface(WINDOW);
		}
	}
	return true;
}

bool loadMedia()
{
	return true;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface(IMAGE);
	IMAGE = NULL;

	//Destroy window
	SDL_DestroyWindow(WINDOW);
	WINDOW = NULL;

	//Quit SDL
	SDL_Quit();
}

int main()
{
	if (init())
	{
		if (loadMedia())
		{
			//Fill the surface white
			SDL_FillRect(SCREENSURFACE, NULL, SDL_MapRGB(SCREENSURFACE->format, 0xFF, 0xFF, 0xFF));

			//update the surface
			SDL_UpdateWindowSurface(WINDOW);

			//wait
			SDL_Delay(2000);
		}
	}

	close();
	return 0;
}
