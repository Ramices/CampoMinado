#pragma once

#ifndef END_GAME_SCREEN_H
#define END_GAME_SCREEN_H

#include "Screen.h"
#include "Texture.h"

class EndGameScreen: public Screen
{
private:
	Texture* title;
	Texture* congratz;
	bool showCongratz;
	TTF_Font* font;
	SDL_Color red;

	int time;

public:
	void setShowCongratz(bool);
	void start(SDL_Renderer*) override;
	void handleEvents(float&) override;
	void update(float&) override;
	void render(SDL_Renderer*) override;
	void close() override;
};

#endif;
