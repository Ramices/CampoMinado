#include "Game.h"
#include "MainScreen.h"
#include "GamePlayScreen.h"
#include "Utils.h"

bool Game::init()
{
	bool success = false;
	if( (SDL_Init(SDL_INIT_EVERYTHING) >= 0) && (IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG) && (TTF_Init() >= 0)  )
	{
		window = SDL_CreateWindow("Campo Minado", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Util::SCREEN_WIDTH, Util::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window)
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (renderer)
			{
				screen = new MainScreen();
				screen->start(renderer);
				success = true;
			}
		}


	}

	return success;
	
}

void Game::start()
{
	float FPS = 60;

	while (!closeGame)
	{
	
		screen->handleEvents(FPS);
		screen->update(FPS);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		screen->render(renderer);

		SDL_RenderPresent(renderer);


		if (screen->changeScreen)
		{

			switch (screen->nextScreen)
			{
				case QUIT_GAME:
					closeGame = true;
					break;

				case GAME_SCREEN:
					screen->close();
					delete(screen);
					screen = new GamePlayScreen();
					screen->start(renderer);
					break;
			}
		}



	}
}

void Game::close()
{
	screen->close();
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();

}

