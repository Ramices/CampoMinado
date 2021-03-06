#pragma once
#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include "Screen.h"
#include "Texture.h"
#include "GamePlayScreen.h"

class GameOverScreen:public Screen
{
private:
	Texture* title;
	int time;
	TTF_Font *font;
public:
	void start(SDL_Renderer*) override;
	void handleEvents(float&) override;
	void update(float&) override;
	void render(SDL_Renderer*) override;
	void close() override;

};

#endif