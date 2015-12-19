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
#include "texture.h"
#include "timer.h"
#include "flake.h"
using namespace std;

//PROTOTYPES
//starts SDL and creates window
bool init();
//loads media
bool loadMedia();
//Frees media and shuts SDL down
void close();

//GLOBAL VARIABLES
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FRAMES_PER_SECOND = 60;
SDL_Window *WINDOW = NULL;
SDL_Renderer *RENDERER = NULL;
SDL_Surface *SCREENSURFACE = NULL;
LTexture background;
LTexture frost;

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
	stringstream path;

	path << cCurrentPath << "/content/background.jpg";
	background.loadFromFile(path.str(), RENDERER);
	if (background.mTexture == NULL)
		return false;

	//clear stringstream
	path.str("");

	path << cCurrentPath << "/content/Frost.png";
	frost.loadFromFile(path.str(), RENDERER);
	if (frost.mTexture == NULL)
		return false;

	return true;
}

void close()
{
	//free loaded images
	background.free();

	//Destroy window
	SDL_DestroyRenderer(RENDERER);
	RENDERER = NULL;
	SDL_DestroyWindow(WINDOW);
	WINDOW = NULL;

	//Quit SDL
	IMG_Quit();
	SDL_Quit();
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
	vector <flake> flakes2;
	vector <flake> flakes3;

	//init SDL
	if (!init())
		return -1;
		
	//load all media
	if (!loadMedia(cCurrentPath))
		return -1;
		
	//main loop flag
	bool quit = false;

	//event handler
	SDL_Event e;

	//mouse location
	int mouse_x = 0, mouse_y = 0;

	//mouse click boolean
	bool click = false;

	//Main loop
	while (!quit)
	{
		//start the frame timer
		fps.start();
		
		//get mouse location
		SDL_GetMouseState(&mouse_x, &mouse_y);
		
		//Handle events in the queue
		while (SDL_PollEvent(&e) != 0)
		{
			//user quits
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				click = true;
			}
			if (e.type == SDL_MOUSEBUTTONUP)
			{
				click = false;
			}
		}
		
		//clear screen
		SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 255);
		SDL_RenderClear(RENDERER);
		
		//stretch & scale background image
		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = SCREEN_WIDTH;
		stretchRect.h = SCREEN_HEIGHT;
		SDL_RenderCopy(RENDERER, background.mTexture, NULL, &stretchRect);
		
		//make flake
		flake *f = new flake(SCREEN_WIDTH, 0);
		flakes.push_back(*f);
		flake *f2 = new flake(SCREEN_WIDTH, 1);
		flakes.push_back(*f2);
		flake *f3 = new flake(SCREEN_WIDTH, 2);
		flakes.push_back(*f3);
		
		//draw flake
		for (int i = 0; i < flakes3.size(); i++) //back flakes
		{
			flakes3.at(i).move();
			if (click)
			{
				flakes3.at(i).on_click(mouse_x, mouse_y);
			}
			if (flakes3.at(i).R.y == SCREEN_HEIGHT)
			{
				flakes3.erase(flakes3.begin() + i);
			}
			else
			{
				SDL_SetRenderDrawColor(RENDERER, flakes3.at(i).r, flakes3.at(i).g, flakes3.at(i).b, flakes3.at(i).a);
				SDL_RenderFillRect(RENDERER, &flakes3.at(i).R);
			}
		}
		for (int i = 0; i < flakes2.size(); i++) //middle flakes
		{
			flakes2.at(i).move();
			if (click)
			{
				flakes2.at(i).on_click(mouse_x, mouse_y);
			}
			if (flakes2.at(i).R.y == SCREEN_HEIGHT)
			{
				flakes2.erase(flakes2.begin() + i);
			}
			else
			{
				SDL_SetRenderDrawColor(RENDERER, flakes2.at(i).r, flakes2.at(i).g, flakes2.at(i).b, flakes2.at(i).a);
				SDL_RenderFillRect(RENDERER, &flakes2.at(i).R);
			}
		}
		for (int i = 0; i < flakes.size(); i++) //front flakes
		{
			flakes.at(i).move();
			if (click)
			{
				flakes.at(i).on_click(mouse_x, mouse_y);
			}
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
		
		
		//add frost texture
		SDL_RenderCopy(RENDERER, frost.mTexture, NULL, &stretchRect);

		//update the screen
		SDL_RenderPresent(RENDERER);
		
		//cap the frame rate
		if (fps.get_ticks() < 1000/FRAMES_PER_SECOND)
			SDL_Delay((1000/FRAMES_PER_SECOND) - fps.get_ticks());
	}

	close();
	return 0;
}
