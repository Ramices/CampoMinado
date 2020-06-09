#pragma once
#ifndef SCREEN_H
#define SCREE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Utils.h"

class Screen
{
protected:
	SDL_Event events;


public:

	GameScreen nextScreen;
	bool changeScreen{ false };


	virtual void start(SDL_Renderer*) = 0;
	virtual void handleEvents(float&);
	virtual void update(float&) = 0;
	virtual void render(SDL_Renderer *) = 0;
	virtual void close() = 0;
};

#endif