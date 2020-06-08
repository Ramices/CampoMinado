#pragma once
#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_h

#include "Screen.h"

class MainScreen: public Screen
{

	 void start()  override;
	 void update(float&) override;
	 void update(SDL_Renderer*) override;
	 void close() override;
};

#endif 

