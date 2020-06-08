#pragma once
#ifndef SCREEN_H
#define SCREE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Utils.h"

class Screen
{
private:
	SDL_Window* window;
	SDL_Event events;


public:

	~Screen();
	GameScreen nextScreen{ GameScreen::MAIN_SCREEN };
	bool changeScreen{ false };


	virtual void start() = 0;
	virtual void update(float&) = 0;
	virtual void update(SDL_Renderer *) = 0;
	virtual void close() = 0;
};

#endif