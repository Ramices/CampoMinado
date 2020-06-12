#include "ScoreScreen.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

void ScoreScreen::start(SDL_Renderer* renderer)
{
	font = TTF_OpenFont("font/arial.ttf", 36);

	title = new Texture(Util::loadTextureFromText("Melhores Scores", renderer, font, SDL_Color{255, 0, 0,255}), 240, 70, 240, 80);
	fstream file("score\\score.txt");

	vector<int> values;
	while(!file.eof())
	{
		int value;
		file >> value;
		values.push_back(value);
	}

	file.close();

	sort(values.begin(), values.end());

	int posY = 180;

	int count = 1;
	for (auto value: values)
	{
		scores.push_back(new Texture(Util::loadTextureFromText(to_string(count) + "º - " + to_string(value), renderer, font, SDL_Color{ 255, 0, 0, 255 }), 300, posY, 120, 50));
		posY += 60;
		++count;
	}

	time = 0;
}
void ScoreScreen::handleEvents(float& deltaTime)
{
	while (SDL_PollEvent(&events) != 0)
	{
		if (events.type == SDL_QUIT)
		{
			closeScreen = true;
		}
	}
}
void ScoreScreen::update(float& deltaTime)
{
	++time;

	if (time == 240)
	{
		changeScreen = true;
		nextScreen = MAIN_SCREEN;
	}
}

void ScoreScreen::render(SDL_Renderer* renderer)
{
	title->render(renderer);

	for (auto score : scores)
	{
		score->render(renderer);
	}
}
void ScoreScreen::close()
{
	delete title;
	for (auto score : scores)
	{
		delete score;
	}
}