#pragma once
#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_h

#include "Screen.h"
#include "Utils.h"
#include "Texture.h"

class MainScreen: public Screen
{

private:
	Texture *menu[Menu::TOTAL_MENU];
	Menu actualOption{Menu::NEW_GAME};
	Menu previousOption{Menu::NEW_GAME };


public: 
	 
	void updateMenu(SDL_Renderer*);
	
	 void start(SDL_Renderer*)  override;
	 void handleEvents(float&) override;
	 void update(float&) override;
	 void render(SDL_Renderer*) override;
	 void close() override;
};

#endif 

