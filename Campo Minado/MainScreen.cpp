#include "MainScreen.h"

void MainScreen::start(SDL_Renderer * renderer)
{
	font = TTF_OpenFont("font/arial.ttf", 36);

	red.r = 255;
	red.g = 0;
	red.b = 0;
	red.a = 255;


	menu[Menu::TITLE] = new Texture(Util::loadTextureFromText("Campo Minado", renderer, font, red), 240, 70, 240, 80);
	menu[Menu::NEW_GAME] = new Texture(Util::loadTextureFromText("Novo jogo", renderer, font, red ), 260, 160, 200, 50);
	menu[Menu::SCORE] = new Texture(Util::loadTextureFromText("Score", renderer, font, red), 260, 220, 200, 50);
	menu[Menu::CONFIG] = new Texture(Util::loadTextureFromText("Configurações", renderer, font, red), 260, 280, 200, 50);
	menu[Menu::QUIT] = new Texture(Util::loadTextureFromText("Sair", renderer, font, red), 260, 340, 200, 50);
	actualOption = Menu::NEW_GAME;


	selectedColor.r = 255;
	selectedColor.g = 122;
	selectedColor.b = 75;
	selectedColor.a = 255;
}


void MainScreen::updateMenu(SDL_Renderer* renderer)
{

	
	switch (previousOption)
	{
	case NEW_GAME:
		menu[previousOption]->setTexture(Util::loadTextureFromText("Novo jogo", renderer, font, red));
		break;
	case SCORE:
		menu[previousOption]->setTexture(Util::loadTextureFromText("Score", renderer, font, red));
		break;
	case QUIT:
		menu[previousOption]->setTexture(Util::loadTextureFromText("Sair", renderer, font, red));
		break;

	case CONFIG:
		menu[previousOption]->setTexture(Util::loadTextureFromText("Configurações", renderer, font, red));
		break;

	}

	switch (actualOption)
	{
	case NEW_GAME:
		menu[actualOption]->setTexture(Util::loadTextureFromText("Novo jogo", renderer, font, selectedColor));
		break;
	case SCORE:
		menu[actualOption]->setTexture(Util::loadTextureFromText("Score", renderer, font, selectedColor));
		break;
	case QUIT:
		menu[actualOption]->setTexture(Util::loadTextureFromText("Sair", renderer, font, selectedColor));
		break;

	case CONFIG:
		menu[actualOption]->setTexture(Util::loadTextureFromText("Configurações", renderer, font, selectedColor));
		break;

	}

}

void MainScreen::handleEvents(float& deltaTime)
{
	while(SDL_PollEvent(&events) != 0)
	{
		if (events.type == SDL_KEYDOWN)
		{
			switch (events.key.keysym.sym)
			{
			case SDLK_UP:
				previousOption = actualOption;
				actualOption = actualOption == NEW_GAME ? QUIT : (Menu)(actualOption-1);
				break;

			case SDLK_DOWN:
				previousOption = actualOption;
				actualOption = actualOption == QUIT ? NEW_GAME : (Menu)(actualOption + 1);
				break;

			case SDLK_SPACE:
				changeScreen = true;

				switch (actualOption)
				{
					case NEW_GAME:
						nextScreen = GameScreen::GAME_SCREEN;
						break;
					case QUIT:
						nextScreen = GameScreen::QUIT_GAME;
						break;

					case SCORE:
						nextScreen = SCORE_SCREEN;
						break;

					case CONFIG:
						nextScreen = OPTION_SCREEN;
						break;


				}
				

			}
		}
	}
}

void MainScreen::update(float& deltaTime)
{

}


void MainScreen::render(SDL_Renderer* renderer)
{
	updateMenu(renderer);

	for (auto item : menu)
	{
		item->render(renderer);
	}
}

void MainScreen::close()
{
	for (auto item : menu)
	{
		delete item;
	}

	TTF_CloseFont(font);

}
