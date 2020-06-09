#pragma once

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>

#include "Screen.h"

class Game
{

public:
	bool init();
	void start();
	void close();
	bool closeGame{ false };

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	Screen* screen = nullptr;
};

#endif