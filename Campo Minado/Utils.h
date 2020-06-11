#ifndef UTIL_H
#define UTIL_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>

class Util
{
	public:
		static SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);
		static SDL_Texture* loadTextureFromText(std::string text, SDL_Renderer* renderer, TTF_Font* font, SDL_Color textColor);
		static const int SCREEN_WIDTH = 720;
		static const int SCREEN_HEIGHT = 630;
};

enum Option
{
	OPTION1 = 0,
	OPTION2,
	OPTION3
};

enum TypeField
{
	FREE,
	DISCOVER,
	FLAG,
	FLAG_MINE,
	FLAG_MINE_DISCOVERY,
	MINE
};


enum  GameScreen
{
	MAIN_SCREEN = 0,
	SCORE_SCREEN,
	GAME_SCREEN,
	GAME_OVER_SCREEN,
	OPTION_SCREEN,
	QUIT_GAME,
	END_GAME_SCREEN,
	TOTAL

};

enum Menu
{
	TITLE = 0,
	NEW_GAME,
	SCORE,
	CONFIG,
	QUIT,
	TOTAL_MENU
};



#endif // !UTIL
