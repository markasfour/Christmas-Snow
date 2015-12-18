#include <iostream>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <time.h>

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "globals.h"
#include "texture.h"
#include "Timer.h"
#include "flake.h"

using namespace std;

//stars SDL and creates window
bool init();

//loads media
bool loadMedia();

//Frees media and shuts SDL down
void close();

//loads individual image
SDL_Surface *loadSurface(string path);


LTexture background;

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
		//set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Warning: Linear texture filtering not enabled.";
		}
		
		//create window
		WINDOW = SDL_CreateWindow( "Christmas Snow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (WINDOW == NULL)
		{
			cout << "Window could not be created. SDL_Error: " << SDL_GetError() << endl;
			return false;
		}
		else
		{
			//create renderer for window
			RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
			if (RENDERER == NULL)
			{
				cout << "Renderer could not be created. SDL_Error: " << SDL_GetError();
				return false;
			}
			else
			{
				//init renderer color
				SDL_SetRenderDrawColor(RENDERER, 0xFF, 0xFF, 0xFF, 0xFF);

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
	}
	return true;
}

bool loadMedia(string cCurrentPath)
{
	//load  stretching surface
	stringstream path;
	path << cCurrentPath << "/content/background.jpg";
	
	background.loadFromFile(path.str());
	//BACKGROUND = loadSurface (path.str());
	//if (BACKGROUND == NULL)
	//{
	//	cout << "Failed to load image." << endl;
	//	return false;
	//}
	
	return true;
}

void close()
{
	//free loaded images
	SDL_FreeSurface(BACKGROUND);
	BACKGROUND = NULL;

	//Destroy window
	SDL_DestroyRenderer(RENDERER);
	RENDERER = NULL;
	SDL_DestroyWindow(WINDOW);
	WINDOW = NULL;

	//Quit SDL
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface *loadSurface(string path)
{
	//final optimized image
	SDL_Surface *optimizedSurface = NULL;

	//load image from path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
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

		//remove old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}

int main()
{
	//set rand seed
	srand(time(NULL));
	
	//get current path to program
	char cCurrentPath[FILENAME_MAX];
	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
     	 return -1;
	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';

	//frame rate regulator
	Timer fps;
	
	//set up flakes
	vector <flake> flakes;

	//init SDL
	if (init())
	{
		//load all media
		if (loadMedia(cCurrentPath))
		{
			//SDL_Texture *background = SDL_CreateTextureFromSurface(RENDERER, BACKGROUND);
			//if (background == NULL) cout << "FUCK" << endl;
			//main loop flag
			bool quit = false;

			//event handler
			SDL_Event e;
			
			//Main loop
			while (!quit)
			{
				//start the frame timer
				fps.start();
				
				//Handle events in the queue
				while (SDL_PollEvent(&e) != 0)
				{
					//user quits
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				
				//clear screen
				SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 255);
				SDL_RenderClear(RENDERER);
				
				//stretch & scale image
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				//background.render(0,0);
				SDL_RenderCopy(RENDERER, background.mTexture, NULL, &stretchRect);
				//SDL_BlitScaled(BACKGROUND, NULL, SCREENSURFACE, &stretchRect);
				
				//update the surface
				//SDL_UpdateWindowSurface(WINDOW);

				//make flake
				flake *f = new flake();
				flakes.push_back(*f);
				
				//draw flake
				for (int i = 0; i < flakes.size(); i++)
				{
					flakes.at(i).move();
					if (flakes.at(i).R.y == SCREEN_HEIGHT)
					{
						flakes.erase(flakes.begin() + i);
					}
					else
					{
						SDL_SetRenderDrawColor(RENDERER, flakes.at(i).r, flakes.at(i).g, flakes.at(i).b, flakes.at(i).a);
						SDL_RenderFillRect(RENDERER, &flakes.at(i).R);
					}
				}
				
				
				//update the screen
				SDL_RenderPresent(RENDERER);
				
				//cap the frame rate
				if (fps.get_ticks() < 1000/FRAMES_PER_SECOND)
					SDL_Delay((1000/FRAMES_PER_SECOND) - fps.get_ticks());
			}
		}
	}

	close();
	return 0;
}
