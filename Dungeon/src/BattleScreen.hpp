#pragma once

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <list>
#include "Hero.hpp"
#include "Glob.hpp"
#include "Mimic.hpp"
#include "CharacterType.hpp"
#include "CharacterAnimationSet.hpp"
#include "HPBar.hpp"
#include "BattleButton.hpp"
#include "BattleEffects.hpp"
#include "ItemMenu.hpp"

using namespace std;

class BattleScreen
{
public:
	SDL_Renderer* renderer;
	SDL_Texture* backgroundTexture;

	Hero* hero;
	int* items;//pointer for our items array

	Character* enemy;

	bool battleFinished = false;
	bool quit = false;
	bool heroesTurn = false;

	SDL_Texture* nameTexture;
	SDL_Rect nameRect;

	CharacterAnimationSet heroAnimationSet;
	CharacterAnimationSet enemyAnimationSet;

	HPBar heroHP;
	HPBar enemyHP;

	BattleButton fightButton;
	BattleButton itemButton;

	int heroDmg = 0, enemyDmg = 0;
	
	BattleEffects battleEffects;
	
	ItemMenu itemMenu;

	BattleScreen(SDL_Renderer* renderer, Hero* hero, int* items, CharacterType enemyType);
	~BattleScreen();
	bool animationsPlaying();
	void useItem();
	void update();
	void draw();
};

