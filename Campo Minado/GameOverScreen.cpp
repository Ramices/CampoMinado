#include "GameOverScreen.h"


void GameOverScreen::start(SDL_Renderer* renderer)
{
	title = new Texture(Util::loadTexture("content\\game_over.png", renderer), 240, 100, 240, 50);
	time = 0;
}
void GameOverScreen::handleEvents(float&)
{

}
void GameOverScreen::update(float& deltaTime)
{
	++time;

	if (time >= 300)
	{
		changeScreen = true;
		nextScreen = MAIN_SCREEN;
	}

}

void GameOverScreen::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	title->render(renderer);
}
void GameOverScreen::close()
{
	delete title;
}