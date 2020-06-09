#include "GamePlayScreen.h"
#include <iostream>

using namespace std;


void GamePlayScreen::start(SDL_Renderer* renderer)
{
	

	widthSquare = 30;
	heightSquare = 30;

	selectedSquare.x = 0;
	selectedSquare.y = 30;
	selectedSquare.w = widthSquare;
	selectedSquare.h = heightSquare;


	totalFieldsDiscovery = 0;
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;
	textColor.a = 255;

	backColor.r = 0;
	backColor.g = 255;
	backColor.b = 0;
	backColor.a = 255;
	


	font = TTF_OpenFont("font/arial.ttf", 32);
	fieldText = new Texture(Util::loadTextureFromText("Campos descobertos: ", renderer, font, textColor), 0, 0, 240, 30);
	numberField = new Texture(Util::loadTextureFromText(to_string(totalFieldsDiscovery), renderer, font, textColor), 241, 5, 30, 20);
	blankSpace = new Texture(Util::loadTexture("content\\blank_space.png", renderer), 0, 0, 0, 0);
}

void GamePlayScreen::handleEvents(float& deltaTime)
{
	while (SDL_PollEvent(&events) != 0)
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
			}

		}
	}
}
void GamePlayScreen::update(float& deltaTime)
{


}

void GamePlayScreen::drawGrid(SDL_Renderer* renderer)
{

	for (int x = 0; x < Util::SCREEN_WIDTH; x += widthSquare)
	{
		for (int y = 30; y < Util::SCREEN_HEIGHT; y += heightSquare)
		{
			blankSpace->render(renderer, x, y, widthSquare, heightSquare);
		}
	}




}


void GamePlayScreen::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, backColor.r, backColor.g, backColor.b, backColor.a);
	SDL_RenderClear(renderer);

	drawGrid(renderer);


	SDL_RenderDrawRect(renderer, &selectedSquare);


	fieldText->render(renderer);
	numberField->render(renderer);

}
 void GamePlayScreen::close() 
{
	 TTF_CloseFont(font);
	 delete(fieldText);
	 delete(numberField);
	 delete blankSpace;

}