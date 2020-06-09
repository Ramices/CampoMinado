#include "Texture.h"


Texture::Texture(SDL_Texture* _texture, int _x, int _y, int _width, int _height)
{
	texture = _texture;
	position.x = _x;
	position.y = _y;
	position.w = _width;
	position.h = _height;

}


void Texture::setTexture(SDL_Texture* _texture)
{
	SDL_DestroyTexture(texture);
	texture = _texture;
}

void Texture::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &position);


}

void Texture::render(SDL_Renderer* renderer, int x, int y, int w, int h)
{
	SDL_Rect customPosition{x, y, w, h};
	SDL_RenderCopy(renderer, texture, NULL, &customPosition);

}

void Texture::destroy()
{
	SDL_DestroyTexture(texture);

}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}