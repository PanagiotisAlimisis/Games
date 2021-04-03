#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

class ItemMenu
{
private:
	SDL_Texture* generateTextTexture(TTF_Font* font, SDL_Color colour, string text);

public:
	SDL_Renderer* renderer;
	int* items;

	SDL_Texture *noItem, *chocolate, *grenade, *atkBoost, *defBoost, *cancel;

	int x, y;
	int selectedItemIndex;

	bool visible = false;

	
	~ItemMenu();
	void setup(SDL_Renderer* renderer, int* items, int x, int y);
	void moveUp();
	void moveDown();
	void draw();
};

