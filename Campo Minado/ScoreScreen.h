#pragma once
#ifndef SCORE_SCREEN_H
#define SCORE_SCREEN_H

#include "Screen.h"
#include "Texture.h"
#include <vector>
#include <SDL_ttf.h>

class ScoreScreen: public Screen
{
private: 
	Texture* title;
	std::vector<Texture *>scores;
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