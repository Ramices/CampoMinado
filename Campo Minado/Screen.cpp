#include "Screen.h"






Screen::~Screen()
{
	SDL_DestroyWindow(window);
}
