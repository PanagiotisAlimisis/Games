#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;


class BattleButton
{
public:
	SDL_Renderer* renderer;
	SDL_Rect buttonRect;
	SDL_Texture *textTexture;
	SDL_Rect textRect;

	bool selected = false;

	~BattleButton();

	void setup(SDL_Renderer* renderer, SDL_Rect buttonRect, string text);
	void draw();
	void drawInactive();//what the buttons look like when the user cannot choose options
};

