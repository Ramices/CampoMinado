#include "EndGameScreen.h"



void EndGameScreen::start(SDL_Renderer* renderer)
{
	title = new Texture(Util::loadTexture("content\\end_game.png", renderer), 240, 100, 240, 50);
	time = 0;
	showCongratz = false;
	congratz = new Texture(Util::loadTexture("content\\end_game.png", renderer), 160, 160, 400, 50);
}

void EndGameScreen::setShowCongratz(bool _congratz)
{
	showCongratz = _congratz;
}

void EndGameScreen::handleEvents(float& deltaTime)
{

}
void EndGameScreen::update(float& deltaTime)
{
	++time;

	if (time >= 300)
	{
		changeScreen = true;
		nextScreen = MAIN_SCREEN;
	}

}
void EndGameScreen::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	title->render(renderer);

	if (showCongratz)
	{
		congratz->render(renderer);
	}

}
void EndGameScreen::close()
{
	delete congratz;
	delete title;
}