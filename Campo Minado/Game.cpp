#include "Game.h"
#include "MainScreen.h"
#include "GamePlayScreen.h"
#include "GameOverScreen.h"
#include "Utils.h"
#include "EndGameScreen.h"

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
	const int FPS = 60;
	const int FramDelay = 1000 / FPS;

	Uint32 frameStart = 0;
	float frameTime = 1.f;

	while (!closeGame)
	{
	
		frameStart = SDL_GetTicks();

		screen->handleEvents(frameTime);
		screen->update(frameTime);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		screen->render(renderer);

		SDL_RenderPresent(renderer);

		frameTime = SDL_GetTicks() - frameStart;

		if (FramDelay > frameTime)
		{
			SDL_Delay(FramDelay - frameTime);
		}

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

				case GAME_OVER_SCREEN:
					screen->close();
					delete(screen);
					screen = new GameOverScreen();
					screen->start(renderer);
					break;
					
				case MAIN_SCREEN:
					screen->close();
					delete(screen);
					screen = new MainScreen();
					screen->start(renderer);
					break;

				case END_GAME_SCREEN:
					screen->close();
					delete(screen);
					screen = new EndGameScreen();
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

