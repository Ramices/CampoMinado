#include "ConfigScreen.h"


void ConfigScreen::start(SDL_Renderer* renderer)
{
	font = TTF_OpenFont("font/arial.ttf", 36);

	red.r = 255;
	red.g = 0;
	red.b = 0;
	red.a = 255;

	selectedSquare.w = 70;
	selectedSquare.h = 60;
	selectedSquare.y = 190;
	selectedSquare.x = 240;


	title = new Texture(Util::loadTextureFromText("Escolha o número de minas:", renderer, font, red), 210, 70, 300, 80);
	options[0] = new Texture(Util::loadTextureFromText("50", renderer, font, red), 250, 200, 50, 50);
	options[1] = new Texture(Util::loadTextureFromText("100 ", renderer, font, red), 340, 200, 50, 50);
	options[2] = new Texture(Util::loadTextureFromText("200", renderer, font, red), 430, 200, 50, 50);

	option = OPTION1;
	numberMines = 50;

}
void ConfigScreen::handleEvents(float& deltaTime)
{
	while (SDL_PollEvent(&events) != 0)
	{
		if (events.type == SDL_KEYDOWN)
		{
			switch (events.key.keysym.sym)
			{
			case SDLK_LEFT:
				option = option == OPTION1 ? OPTION3 : (Option)(option - 1);
				break;

			case SDLK_RIGHT:
				option = option == OPTION3 ? OPTION1 : (Option)(option + 1);
				break;

			case SDLK_SPACE:

				switch (option)
				{
				case OPTION1:
					numberMines = 50;
					break;
				case OPTION2:
					numberMines = 100;
					break;
				case OPTION3:
					numberMines = 150;
					break;


					 
				}

				changeScreen = true;
				nextScreen = MAIN_SCREEN;

				break;
				

			}
		}
	}
}
void ConfigScreen::update(float& deltaTime)
{

}

void ConfigScreen::render(SDL_Renderer* renderer)
{
	
	
	switch (option)
	{


		case OPTION1:
			selectedSquare.x = 240;
		break;
		
		case OPTION2:
			selectedSquare.x = 330;
		break;
		
		case OPTION3:
			selectedSquare.x = 420;
		break;


	}

	title->render(renderer);

	for (auto option : options)
		option->render(renderer);

	SDL_SetRenderDrawColor(renderer, red.r, red.g, red.b, red.a);
	SDL_RenderDrawRect(renderer, &selectedSquare);


}
void ConfigScreen::close()
{
	delete title;

	for (auto option : options)
		delete option;

	TTF_CloseFont(font);
}
