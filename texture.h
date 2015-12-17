#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "globals.h"
using namespace std;

//Texture wrapper class
class LTexture
{
	public: 
		//init variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//loads image from path
		bool loadFromFile(string path);

		//renders texture at given point
		void render(int x, int y);

		//deallocates texture
		void free();

		//gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//the actual hardware texture
		SDL_Texture *mTexture;

		//image dimensions
		int mWidth;
		int mHeight;
};

LTexture::LTexture()
{
	//init
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//deallocate
	free();
}

bool LTexture::loadFromFile(string path)
{
	//remove preexisting texture
	free();

	//the final texture
	SDL_Texture *newTexture = NULL;

	//load image from path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "Unable to load image. SDL_image Error: " << IMG_GetError();
	}
	else
	{
		//color key image
		//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		
		//create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(RENDERER, loadedSurface);
		if (newTexture == NULL)
		{
			cout << "Unable to crate texture. SDL_Error: " << SDL_GetError();
		}
		else
		{
			//get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//remove old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(int x, int y)
{
	//set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};
	SDL_RenderCopy(RENDERER, mTexture, NULL, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

#endif
