#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

//load individual image
SDL_Surface* loadSurface(string path);

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
			//init PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				cout << "SDL_image could not initialize. SDL_image Error: " << IMG_GetError();
				return false;
			}
			//get window surface
			SCREENSURFACE = SDL_GetWindowSurface(WINDOW);
		}
	}
	return true;
}

bool loadMedia()
{
	//Load image
	IMAGE = loadSurface("./content/background.png");
	if (IMAGE == NULL)
	{
		cout << "Failed to load image." << endl;
		return false;
	}
	
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
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface(string path)
{
	//final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "Unable to load image. SDL_image Error: " << IMG_GetError();
	}
	else
	{
		//convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, SCREENSURFACE->format, NULL);
		if (optimizedSurface == NULL)
		{
			cout << "Unable to optimize image. SDL_Error: " << SDL_GetError();
		}

		//discard old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}

int main()
{
	if (init())
	{
		if (loadMedia())
		{
			//main loop flag
			bool quit = false;

			//event handler
			SDL_Event e;

			//while application is running
			while (!quit)
			{
				//Handle events in the queue
				while (SDL_PollEvent(&e) != 0)
				{
					//user quits
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				
				//stretch & scale image
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;

				//apply the image to surface
				SDL_BlitScaled(IMAGE, NULL, SCREENSURFACE, &stretchRect);

				//update the surface
				SDL_UpdateWindowSurface(WINDOW);
			}
		}
	}

	close();
	return 0;
}
