#pragma once
#ifndef GAMEPLAY_SCREEN_H
#define GAMEPLAY_SCREEN_H

#include "Screen.h"
#include "Texture.h"
#include <SDL_ttf.h>
#include <vector>

class GamePlayScreen: public Screen
{
public:
	 GamePlayScreen(int);
	 void activePowerUp();
	 void start(SDL_Renderer*);
	 void handleEvents(float&);
	 void update(float&);
	 void render(SDL_Renderer*) ;
	 void close();
	 void drawGrid(SDL_Renderer * renderer);

	 bool isEndGame();
	 int totalTime{ 0 };
	 void setNumberMines(int);
	 int numberPowerUp;
	 Texture* textNumberPowerUp;

private:

	TTF_Font* font;
	Texture *timeText;
	Texture* timeNumber;
	Texture* blankSpace;
	Texture* flagSpace;
	Texture* discoverSpace;
	Texture* mineSpace;
	Texture* skySpace;



	int widthSquare;
	int heightSquare;
	
	SDL_Rect selectedSquare;
	SDL_Color black{ 0, 0, 0, 255 };


	SDL_Color textColor;
	int timeEndGame{ 0 };

	std::vector<std::vector<TypeField>> field;
	std::vector<Texture*> fieldsDiscovery;

	SDL_Renderer* renderer;

	int numberMines;
	bool endGame;


};
#endif

