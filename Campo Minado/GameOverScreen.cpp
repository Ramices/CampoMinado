#include "GameOverScreen.h"


void GameOverScreen::start(SDL_Renderer* renderer)
{
	font = TTF_OpenFont("font/arial.ttf", 36);

	title = new Texture(Util::loadTextureFromText("Game Over", renderer, font, SDL_Color{ 255, 0, 0,255 }), 240, 70, 240, 80);
	time = 0;
}
void GameOverScreen::handleEvents(float& deltaTime)
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

	TTF_CloseFont(font);
	delete title;
}