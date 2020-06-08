#include "Game.h"

void Game::init()
{
	if( (!SDL_Init(SDL_INIT_EVERYTHING)) && (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) && !(TTF_Init())  )
	{
	

	}

}

void Game::start()
{

}

void Game::close()
{
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}

