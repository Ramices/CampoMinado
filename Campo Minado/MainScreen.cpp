#include "MainScreen.h"

void MainScreen::start(SDL_Renderer * renderer)
{
	menu[Menu::TITLE] = new Texture (Util::loadTexture("content\\title.png", renderer), 240, 100, 240, 50 );
	menu[Menu::NEW_GAME] = new Texture(Util::loadTexture("content\\novo_jogo.png", renderer), 260, 160, 200, 50);
	menu[Menu::SCORE] = new Texture(Util::loadTexture("content\\score.png", renderer), 260, 220, 200, 50);
	menu[Menu::CONFIG] = new Texture(Util::loadTexture("content\\config.png", renderer), 260, 280, 200, 50);
	menu[Menu::QUIT] = new Texture(Util::loadTexture("content\\sair.png", renderer), 260, 340, 200, 50);
	actualOption = Menu::NEW_GAME;


}


void MainScreen::updateMenu(SDL_Renderer* renderer)
{

	
	switch (previousOption)
	{
	case NEW_GAME:
		menu[previousOption]->setTexture(Util::loadTexture("content\\novo_jogo.png", renderer));
		break;
	case SCORE:
		menu[previousOption]->setTexture(Util::loadTexture("content\\score.png", renderer));
		break;
	case QUIT:
		menu[previousOption]->setTexture(Util::loadTexture("content\\sair.png", renderer));
		break;

	case CONFIG:
		menu[previousOption]->setTexture(Util::loadTexture("content\\config.png", renderer));
		break;

	}

	switch (actualOption)
	{
	case NEW_GAME:
		menu[actualOption]->setTexture(Util::loadTexture("content\\novo_jogo_selecionado.png", renderer));
		break;
	case SCORE:
		menu[actualOption]->setTexture(Util::loadTexture("content\\score_selecionado.png", renderer));
		break;
	case QUIT:
		menu[actualOption]->setTexture(Util::loadTexture("content\\sair_selecionado.png", renderer));
		break;

	case CONFIG:
		menu[actualOption]->setTexture(Util::loadTexture("content\\config_selecionado.png", renderer));
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
}