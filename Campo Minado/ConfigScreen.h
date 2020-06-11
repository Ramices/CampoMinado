#pragma once
#ifndef CONFIG_SCREEN_H
#define CONFIG_SCREEN_H

#include "Screen.h"
#include "Texture.h"

class ConfigScreen : public Screen
{

private:
	TTF_Font* font;

	Texture* title;
	Texture* options[3];
	SDL_Color red;
	Option option;
	SDL_Rect selectedSquare;


public:
	void start(SDL_Renderer*) override;
	void handleEvents(float&) override;
	void update(float&) override;
	void render(SDL_Renderer*) override;
	void close() override;
	int numberMines;

};

#endif