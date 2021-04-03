#pragma once
#include "AnimationManager.hpp"
#include "CharacterType.hpp"

using namespace std;

class CharacterAnimationSet
{
public:
	int x, y;
	SDL_Renderer* renderer;
	Animation idle, attack, hit;
	AnimationManager animationManager;

	//for animations that play once then return to idle
	bool doAction = false;

	void setup(SDL_Renderer* renderer, int x, int y, CharacterType type);
	void doIdle();
	void doAttack();
	void doHit();

	void update(float dt);
	void draw();
};

