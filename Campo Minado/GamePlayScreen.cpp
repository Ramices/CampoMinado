#include "GamePlayScreen.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

void GamePlayScreen::setNumberMines(int number)
{
	numberMines = number;
}

void GamePlayScreen::start(SDL_Renderer* renderer)
{ 
	this->renderer = renderer;
	numberPowerUp = 3;
	timeEndGame = 0;
	widthSquare = 30;
	heightSquare = 30;

	selectedSquare.x = 0;
	selectedSquare.y = 30;
	selectedSquare.w = widthSquare;
	selectedSquare.h = heightSquare;


	totalTime = 123;
	textColor.r = 34;
	textColor.g = 72;
	textColor.b = 24;
	textColor.a = 255;

	

	font = TTF_OpenFont("font/arial.ttf", 36);
	timeText = new Texture(Util::loadTextureFromText("Tempo decorrido: ", renderer, font, textColor), 0, 0, 240, 30);
	timeNumber = new Texture(Util::loadTextureFromText(to_string(totalTime), renderer, font, textColor), 241, 5, 30, 20);
	blankSpace = new Texture(Util::loadTexture("content\\blank_space.png", renderer), 0, 0, 0, 0);
	flagSpace = new Texture(Util::loadTexture("content\\flag_space.png", renderer), 0, 0, 0, 0);
	discoverSpace = new Texture(Util::loadTexture("content\\discover_space.png", renderer), 0, 0, 0, 0);
	mineSpace = new Texture(Util::loadTexture("content\\mine_space.png", renderer), 0, 0, 0, 0);
	skySpace = new Texture(Util::loadTexture("content\\sky_space.png", renderer), 0, 0, 0, 0);
	textNumberPowerUp = new Texture(Util::loadTextureFromText("Número de PowerUps: " + to_string(numberPowerUp), renderer, font, textColor), 460, 0, 240, 30);

	default_random_engine engine(time(0));
	uniform_int_distribution<unsigned int> rand(1, 10 );

	field.resize(static_cast<int>(Util::SCREEN_WIDTH / widthSquare));
	for (int i = 0; i < Util::SCREEN_WIDTH/widthSquare; ++i)
	{
		field[i].resize(static_cast<int>((Util::SCREEN_HEIGHT-30) / heightSquare));
	}

	int totalMine = 0;

	while (totalMine < numberMines)
	{
		for (int i = 0; i < field.size(); ++i)
		{

			for (int j = 0; j < field[i].size(); ++j)
			{
				if (field[i][j] == MINE)
					continue;

				if (rand(engine) <= 2  && totalMine < numberMines)
				{
					field[i][j] = MINE;
					++totalMine;
				}
			}
		}
	}

	endGame = false;
}
void GamePlayScreen::activePowerUp()
{
	bool breakPower = false;
	for (int i = 0; i < field.size() && !breakPower; ++i)
	{

		for (int j = 0; j < field[i].size() && !breakPower; ++j)
		{
			if (field[i][j] == MINE)
			{
				field[i][j] = FLAG_MINE_DISCOVERY;
				breakPower = true;
			}
			
		}
	}
}

void GamePlayScreen::handleEvents(float& deltaTime)
{
	if (endGame)
		return;

	while (SDL_PollEvent(&events) != 0 )
	{
		if (events.type == SDL_KEYDOWN)
		{
			switch (events.key.keysym.sym)
			{
			case SDLK_UP:
				selectedSquare.y = ((selectedSquare.y - heightSquare) < 30) ? selectedSquare.y : (selectedSquare.y - heightSquare);

				break;

			case SDLK_DOWN:
				selectedSquare.y = ((selectedSquare.y + heightSquare) >= Util::SCREEN_HEIGHT) ? selectedSquare.y : (selectedSquare.y + heightSquare);

				break;

			case SDLK_LEFT:
				selectedSquare.x = ((selectedSquare.x - widthSquare) < 0) ? selectedSquare.x : (selectedSquare.x - widthSquare);

				break;

			case SDLK_RIGHT:
				selectedSquare.x = ((selectedSquare.x + widthSquare) >= Util::SCREEN_WIDTH) ? selectedSquare.x : (selectedSquare.x + widthSquare);
				break;

			case SDLK_p:
				if (numberPowerUp > 0)
				{
					--numberPowerUp;
					textNumberPowerUp->setTexture(Util::loadTextureFromText("Número de PowerUps: " + to_string(numberPowerUp), renderer, font, textColor));
					activePowerUp();
				}

			break;

			case SDLK_f:
			{
				int x = static_cast<int>(selectedSquare.x / widthSquare);
				int y = static_cast<int>((selectedSquare.y - 30) / heightSquare);

				if (field[x][y] == FREE)
				{
					field[x][y] = FLAG;
				}
				else
				if (field[x][y] == FLAG_MINE)
				{
					field[x][y] = MINE;
				}
				else
				if (field[x][y] == MINE)
				{
					field[x][y] = FLAG_MINE;
				}
				else
				if (field[x][y] == FLAG)
				{
					field[x][y] = FREE;
				}

			}

				break;


			case SDLK_SPACE:


				int posX = static_cast<int>(selectedSquare.x / widthSquare);
				int posY = static_cast<int>((selectedSquare.y - 30) / heightSquare);

				if (field[posX][posY] == MINE || field[posX][posY] == FLAG_MINE || field[posX][posY] ==FLAG_MINE_DISCOVERY)
				{
					endGame = true;
				}
				else
				if (field[posX][posY] == FREE || field[posX][posY] == FLAG)
				{
					int totalMinesRound = 0;
					vector<SDL_Point> points;

					if ((posY + 1) <= field[0].size())
					{
						//Baixo
						if ((field[posX][posY + 1] == MINE || field[posX][posY+1] == FLAG_MINE || field[posX][posY + 1]== FLAG_MINE_DISCOVERY))
						{
							++totalMinesRound;
						}
						else
						{
							points.push_back(SDL_Point{posX, posY+1});
						}

					}

					if ((posY - 1) >= 0)
					{
						//Cima
						if (field[posX][posY - 1] == MINE || field[posX][posY - 1] == FLAG_MINE || field[posX][posY - 1] == FLAG_MINE_DISCOVERY)
						{
							++totalMinesRound;
						}
						else
						{
							points.push_back(SDL_Point{ posX, posY-1 });
						}


					}

					if ((posX + 1) < field.size())
					{

						//Direita
						if (field[posX + 1][posY] == MINE || field[posX+1][posY] == FLAG_MINE || field[posX+1][posY] == FLAG_MINE_DISCOVERY)
 						{

							++totalMinesRound;
						}
						else
						{
							points.push_back(SDL_Point{ posX+1, posY });
						}


						if ((posY - 1) >= 0)
						{
							//Nordeste
							if (field[posX + 1][posY - 1] == MINE || field[posX+1][posY-1] == FLAG_MINE || field[posX+1][posY - 1] == FLAG_MINE_DISCOVERY)
							{
								++totalMinesRound;
							}
							else
							{
								points.push_back(SDL_Point{ posX+1, posY-1 });
							}
						}

						if ((posY + 1) <= field[0].size())
						{
							//Sudeste
							if (field[posX + 1][posY + 1] == MINE || field[posX+1][posY+1] == FLAG_MINE || field[posX+1][posY + 1] == FLAG_MINE_DISCOVERY)
							{
								++totalMinesRound;
							}
							else
							{
								points.push_back(SDL_Point{ posX+1, posY+1 });
							}
						}


					}

					if ((posX - 1) >= 0)
					{
						//esquerda
						if (field[posX - 1][posY] == MINE || field[posX-1][posY] == FLAG_MINE || field[posX-1][posY] == FLAG_MINE_DISCOVERY)
						{

							++totalMinesRound;
						}
						else
						{
							points.push_back(SDL_Point{ posX-1, posY });
						}

						if ((posY - 1) >= 0)
						{
							//Noroeste
							if (field[posX - 1][posY - 1] == MINE || field[posX -1][posY -1] == FLAG_MINE || field[posX -1][posY -1 ] == FLAG_MINE_DISCOVERY)
							{

								++totalMinesRound;
							}
							else
							{
								points.push_back(SDL_Point{ posX-1, posY -1});
							}
						}

						if ((posY + 1) <= field[0].size())
						{
							//Sudoeste
							if (field[posX - 1][posY + 1] == MINE || field[posX-1][posY+1] == FLAG_MINE ||  field[posX-1][posY + 1] == FLAG_MINE_DISCOVERY)
							{
								++totalMinesRound;
							}
							else
							{
								points.push_back(SDL_Point{ posX-1, posY+1 });
							}
						}	
					
					}
					if (totalMinesRound == 0)
					{
						points.push_back(SDL_Point{ posX, posY });

						for (auto point : points)
						{
							field[point.x][point.y] = DISCOVER;
						}
					}
					else
					{
						field[posX][posY] = DISCOVER;
						fieldsDiscovery.push_back(new Texture(Util::loadTextureFromText(to_string(totalMinesRound), renderer, font, SDL_Color{ 255, 255, 255, 255 }), selectedSquare.x, selectedSquare.y, widthSquare, heightSquare));					
					}

				}

				break;



			}

		}
	}
}


bool GamePlayScreen::isEndGame()
{

	for (int i = 0; i < field.size(); ++i)
	{

		for (int j = 0; j < field[i].size(); ++j)
		{
			if (field[i][j] == FREE || field[i][j] == FLAG )
			{
				return false;
			}

		}
	}

	return true;
}

void GamePlayScreen::update(float& deltaTime)
{



	if (endGame )
	{

		if (timeEndGame >= 180)
		{
			changeScreen = true;
			nextScreen = GAME_OVER_SCREEN;

		}
		++timeEndGame;

	}
	else
	{
		++totalTime;

		if (isEndGame())
		{
			changeScreen = true;
			nextScreen = END_GAME_SCREEN;

		}
	}

}

void GamePlayScreen::drawGrid(SDL_Renderer* renderer)
{

	for (int x = 0; x < Util::SCREEN_WIDTH; x += widthSquare)
	{
		for (int y = 30; y < Util::SCREEN_HEIGHT; y += heightSquare)
		{
			int posX = static_cast<int>(x / widthSquare);
			int posY = static_cast<int>((y - 30) / heightSquare);


			if (endGame && (field[posX][posY] == MINE || field[posX][posY] == FLAG_MINE))
			{
				mineSpace->render(renderer, x, y, widthSquare, heightSquare);
			}
			else
			if (field[posX][posY] == FLAG || field[posX][posY] == FLAG_MINE)
			{

				flagSpace->render(renderer, x, y, widthSquare, heightSquare);
			}
			else
			if (field[posX][posY] == DISCOVER)
			{
				discoverSpace->render(renderer, x, y, widthSquare, heightSquare);					
			}
			else if (field[posX][posY] == FLAG_MINE_DISCOVERY)
			{
				mineSpace->render(renderer, x, y, widthSquare, heightSquare);								
			}
			else
			{
				blankSpace->render(renderer, x, y, widthSquare, heightSquare);
			}


		}
	}

}

GamePlayScreen::GamePlayScreen(int _numberMines)
{
	numberMines = _numberMines;
}

void GamePlayScreen::render(SDL_Renderer* renderer)
{

	for (int x = 0; x < Util::SCREEN_WIDTH; x += 30)
	{
		skySpace->render(renderer, x, 0, widthSquare, heightSquare);

	}
	


	timeNumber->setTexture(Util::loadTextureFromText(to_string(static_cast<int>(totalTime / 60)), renderer, font, textColor));
	timeText->render(renderer);
	timeNumber->render(renderer);
	textNumberPowerUp->render(renderer);

	drawGrid(renderer);

	SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
	SDL_RenderDrawRect(renderer, &selectedSquare);



	for (auto field : fieldsDiscovery)
	{
		field->render(renderer);
	}



}
 void GamePlayScreen::close() 
{
	 TTF_CloseFont(font);
	 delete(timeText);
	 delete(timeNumber);
	 delete blankSpace;
	 delete flagSpace;
	 delete discoverSpace;
	 delete mineSpace;
	 delete skySpace;
	 delete textNumberPowerUp;
	 for (auto field : fieldsDiscovery)
	 {
		 delete field;
	 }

}