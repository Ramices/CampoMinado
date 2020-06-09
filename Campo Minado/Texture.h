#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>


class Texture
{
private:
	SDL_Texture* texture = nullptr;
	SDL_Rect position;
	

public:
	void destroy();
	void setTexture(SDL_Texture*);
	Texture(SDL_Texture *, int, int, int ,int);
	void render(SDL_Renderer*);
	void render(SDL_Renderer* renderer, int, int, int, int);
	~Texture();
};

#endif