#include "Game.h"
#include "MainScreen.h"
#include "GamePlayScreen.h"
#include "GameOverScreen.h"
#include "Utils.h"
#include "EndGameScreen.h"
#include "ScoreScreen.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include "ConfigScreen.h"

using namespace std;

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
	numberOfMines = 100;
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
					screen = new GamePlayScreen(numberOfMines);
					screen->start(renderer);
					break;

				case GAME_OVER_SCREEN:
					screen->close();
					delete(screen);
					screen = new GameOverScreen();
					screen->start(renderer);
					break;

				case OPTION_SCREEN:
					screen->close();
					delete(screen);
					screen = new ConfigScreen();
					screen->start(renderer);
					break;


				case MAIN_SCREEN:
				{
					
					auto actualScreen = dynamic_cast<ConfigScreen*>(screen);
					if (actualScreen)
					{
						numberOfMines = actualScreen->numberMines;
					}
					screen->close();
					delete(screen);
					

					screen = new MainScreen();
					screen->start(renderer);
				}
					break;

				case END_GAME_SCREEN:

				{
					fstream file("score\\score.txt");
					vector<int> values;
					bool showCongratz = false;


					while (!file.eof())
					{
						int value;
						file >> value;
						values.push_back(value);
					}
					file.close();
					ofstream fileWrite("score\\score.txt", ios::in || ios::out || ios::trunc);

					int gameTime = ((GamePlayScreen*)screen)->totalTime/60;
					

					if (values.size() == 0)
					{
						showCongratz = true;
						values.push_back(gameTime);
					}
					else
					{
						for (auto &value : values)
						{

							if (gameTime <= value)
							{
								showCongratz = true;
								value = gameTime;
								break;
							}
						}
					}
					sort(values.begin(), values.end());

					for (int i =0; i < values.size(); ++i)
					{
						fileWrite << values[i];

						if (i + 1 != values.size())
							fileWrite << endl;
					}


					fileWrite.close();


					screen->close();
					delete(screen);
					screen = new EndGameScreen();
					screen->start(renderer);
					((EndGameScreen*)screen)->setShowCongratz(showCongratz);
				}
					break;

				case SCORE_SCREEN:
					screen->close();
					delete(screen);
					screen = new ScoreScreen();
					screen->start(renderer);
					break;


			}


		}


		closeGame = screen->closeScreen;

	}

}

void Game::close()
{
	screen->close();
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();

}

