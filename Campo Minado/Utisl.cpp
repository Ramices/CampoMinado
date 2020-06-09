#include "Utils.h"

SDL_Texture*  Util::loadTexture(std::string path, SDL_Renderer* renderer)
{
	SDL_Surface* surface = IMG_Load(path.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	return texture;

}

SDL_Texture* Util::loadTextureFromText(std::string text, SDL_Renderer* renderer, TTF_Font* font, SDL_Color textColor)
{
    SDL_Texture* texture;
 
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);   
    SDL_FreeSurface(textSurface);


    return texture;
}