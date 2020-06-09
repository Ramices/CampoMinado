#pragma once
#ifndef GAMEPLAY_SCREEN_H
#define GAMEPLAY_SCREEN_H

#include "Screen.h"
#include "Texture.h"
#include <SDL_ttf.h>

class GamePlayScreen: public Screen
{
public:
	 void start(SDL_Renderer*);
	 void handleEvents(float&);
	 void update(float&);
	 void render(SDL_Renderer*) ;
	 void close();
	 void drawGrid(SDL_Renderer * renderer);

private:

	TTF_Font* font;
	Texture *fieldText;
	Texture* numberField;
	Texture* blankSpace;
	int widthSquare;
	int heightSquare;
	
	SDL_Rect selectedSquare;

	SDL_Color textColor;
	SDL_Color backColor;
	int totalFieldsDiscovery{ 0 };

};
#endif

