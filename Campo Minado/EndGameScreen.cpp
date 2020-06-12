#include "EndGameScreen.h"



void EndGameScreen::start(SDL_Renderer* renderer)
{
	red.r = 255;
	red.g = 0;
	red.b = 0;
	red.a = 255;
	font = TTF_OpenFont("font/arial.ttf", 36);

	title = new Texture(Util::loadTextureFromText("Parabéns! Você venceu", renderer, font, red), 240, 100, 240, 50);
	congratz = new Texture(Util::loadTextureFromText("VOCÊ FEZ UM NOVO RECORDE", renderer, font, red), 160, 160, 400, 50);

	time = 0;
	showCongratz = false;
}

void EndGameScreen::setShowCongratz(bool _congratz)
{
	showCongratz = _congratz;
}

void EndGameScreen::handleEvents(float& deltaTime)
{
	while (SDL_PollEvent(&events) != 0)
	{
		if (events.type == SDL_QUIT)
		{
			closeScreen = true;
		}
	}
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