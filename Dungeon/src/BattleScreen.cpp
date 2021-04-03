#include "BattleScreen.hpp"


BattleScreen::BattleScreen(SDL_Renderer * renderer, Hero * hero, int * items, CharacterType enemyType)
{
	//if incorrect enemy type put in, default to glob
	if (enemyType != globType && enemyType != mimicType)
		enemyType = globType;

	this->renderer = renderer;
	this->hero = hero;
	this->items = items;

	//load background texture
	backgroundTexture = IMG_LoadTexture(renderer, "../assets/bg.png");

	//Create Name Texture
	TTF_Font* font = TTF_OpenFont("../assets/vermin_vibes_1989.ttf", 16);
	SDL_Color textColor = { 0,0,0,0 };
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, hero->getName().c_str(), textColor);
	nameTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
	//setup name texture drawing destination rectangle
	nameRect.x = 90;
	nameRect.y = 180;
	SDL_QueryTexture(nameTexture, NULL, NULL, &nameRect.w, &nameRect.h);

	//setup animations
	heroAnimationSet.setup(renderer, 47, 181, heroType);
	enemyAnimationSet.setup(renderer, 246, 114, enemyType);

	if (enemyType == globType)
		enemy = new Glob();
	else if (enemyType == mimicType)
		enemy = new Mimic();

	//setup health bars
	heroHP.setup(renderer, 90, 194);
	enemyHP.setup(renderer, 190, 10);

	//setup buttons
	fightButton.setup(renderer, { 0,180,80,30 }, "Fight");
	fightButton.selected = true;
	itemButton.setup(renderer, { 0,210,80,30 }, "Item");

	//decide who goes first
	if (hero->getAGI() > enemy->getAGI())
		heroesTurn = true;
	else
		heroesTurn = false;

	//setup battle effects
	battleEffects.setup(renderer, enemyAnimationSet.x, enemyAnimationSet.y);

	//setup item menu
	itemMenu.setup(renderer, items, 0, 0);
}


BattleScreen::~BattleScreen()
{
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(nameTexture);
}


bool BattleScreen::animationsPlaying()
{
	bool animating = heroAnimationSet.doAction || enemyAnimationSet.doAction || battleEffects.doAction;
	return animating;
}


void BattleScreen::useItem()
{
	if (items[itemMenu.selectedItemIndex] == 1)
	{
		//was chocolate, lets heal
		battleEffects.setXY(heroAnimationSet.x, heroAnimationSet.y);
		battleEffects.doHeal();

		hero->heal(10);
	}
	else if (items[itemMenu.selectedItemIndex] == 2)
	{
		//grenade!
		battleEffects.setXY(enemyAnimationSet.x, enemyAnimationSet.y);
		battleEffects.doExplode();

		enemyDmg = 20;
	}
	else if (items[itemMenu.selectedItemIndex] == 3)
	{
		//atk boost 
		battleEffects.setXY(heroAnimationSet.x, heroAnimationSet.y);
		battleEffects.doAtkBoost();

		hero->atkBoost(2);
	}
	else if (items[itemMenu.selectedItemIndex] == 4)
	{
		//def boost 
		battleEffects.setXY(heroAnimationSet.x, heroAnimationSet.y);
		battleEffects.doDefBoost();

		hero->defBoost(2);
	}
	//clear item from inventory
	items[itemMenu.selectedItemIndex] = 0;

	//change turns
	heroesTurn = false;
}


void BattleScreen::update()
{
	//timing setup
	//deltaTime(measurement of time per frame render as fraction of 1 second e.g 0.5 = 500ms)
	float dt = 0;
	//last time we worked out deltaTime
	Uint32 lastUpdate = SDL_GetTicks();

	while (!battleFinished)
	{
		//update our delta time
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		dt = timeDiff / 1000.0f;
		lastUpdate = SDL_GetTicks();//update this so we get correct diff

		SDL_Event sdlEvent;
		//loop through input events and copy their details one by one into our sdlEvent variable
		while (SDL_PollEvent(&sdlEvent))
		{
			//event when user clicks close window button
			if (sdlEvent.type == SDL_QUIT)
			{
				quit = true;
			}
			//if a button was pressed
			if (sdlEvent.type == SDL_KEYDOWN)
			{
				//then check which button
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					quit = true;
				}
				else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP)
				{
					if (heroesTurn)
					{
						if (itemMenu.visible)
						{
							itemMenu.moveUp();
						}
						else
						{
							fightButton.selected = true;
							itemButton.selected = false;
						}
					}
				}
				else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					if (heroesTurn)
					{
						if (itemMenu.visible)
						{
							itemMenu.moveDown();
						}
						else
						{
							fightButton.selected = false;
							itemButton.selected = true;
						}
					}
				}
				else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE && sdlEvent.key.repeat == 0)
				{
					if (heroesTurn && !animationsPlaying())
					{
						if (itemMenu.visible)
						{
							//if selected item was cancel or a noItem, do nothing
							if (itemMenu.selectedItemIndex == 10 || items[itemMenu.selectedItemIndex] == 0)
							{
								//do nothing, just need to close the item window
							}
							else
							{
								//use item
								useItem();
							}
							itemMenu.visible = false;
						}
						else if (fightButton.selected)
						{
							//punch 
							heroAnimationSet.doAttack();
							enemyDmg = hero->getDamage();
							heroesTurn = false;
						}
						else if (itemButton.selected)
						{
							//show item menu
							itemMenu.visible = true;
						}
					}
				}
			}
		}
		//exit battle if close window or press ESC
		if (quit)
			battleFinished = true;

		//update character states
		if (!animationsPlaying()) {
			if (hero->getHP() <= 0 || enemy->getHP() <= 0)
			{
				//if anyone is dead, battle over
				battleFinished = true;
			}
			else if (heroDmg > 0)
			{
				hero->takeDamage(heroDmg);
				heroAnimationSet.doHit();

				battleEffects.setXY(heroAnimationSet.x, heroAnimationSet.y);
				battleEffects.doHit();

				heroDmg = 0;
			}
			else if (enemyDmg > 0)
			{
				enemy->takeDamage(enemyDmg);
				enemyAnimationSet.doHit();

				battleEffects.setXY(enemyAnimationSet.x, enemyAnimationSet.y);
				battleEffects.doHit();

				enemyDmg = 0;
			}
			else if (!heroesTurn)
			{
				//ENEMY ATTACK
				enemyAnimationSet.doAttack();
				heroDmg = enemy->getDamage();
				heroesTurn = true;
			}
		}

		//update animations
		heroAnimationSet.update(dt);
		enemyAnimationSet.update(dt);

		//update health bars
		heroHP.hp = hero->getHP();
		heroHP.hpMax = hero->getHPMax();

		enemyHP.hp = enemy->getHP();
		enemyHP.hpMax = enemy->getHPMax();

		//update battle effect animations
		battleEffects.update(dt);

		draw();
	}
}


void BattleScreen::draw()
{
	//clear the screen
	SDL_SetRenderDrawColor(renderer, 21, 209, 249, 255);
	SDL_RenderClear(renderer);

	//draw bg
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	//draw enemy
	enemyAnimationSet.draw();

	//draw hero
	heroAnimationSet.draw();

	//ui bottom bar
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect bottomUIBar = { 0,180, 320, 60 };//x,y,w,h
	SDL_RenderFillRect(renderer, &bottomUIBar);
	//draw border too
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &bottomUIBar);

	//draw name
	SDL_RenderCopy(renderer, nameTexture, NULL, &nameRect);
	
	//draw HP bars
	heroHP.draw();
	enemyHP.draw();

	//draw buttons
	fightButton.draw();
	itemButton.draw();

	//draw item menu
	itemMenu.draw();

	//draw effects
	battleEffects.draw();

	//present frame to screen
	SDL_RenderPresent(renderer);
}
