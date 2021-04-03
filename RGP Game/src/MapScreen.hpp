#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Hero.hpp"
#include "MapObject.hpp"
#include <list>

#include <fstream>
#include "InfoBox.hpp"

#include <stdlib.h>
#include <time.h>

#include "BattleScreen.hpp"

using namespace std;

class MapScreen
{
public:
	Hero* hero;
	int* items;

	SDL_Renderer* renderer;

	int map[10][10];
	MapObject heroObj;
	MapObject door;
	list<MapObject> mapObjects;

	SDL_Texture *heroTexture, *doorTexture, *globTexture, *chestTexture;

	bool quit = false;
	bool escaped = false;
	bool doorLocked = true;

	InfoBox infoBox;

	MapScreen(SDL_Renderer* renderer, Hero* hero, int* items);
	~MapScreen();

	void itemFound();

	void update();
	void draw();
};

