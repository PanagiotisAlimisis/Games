#include "MapScreen.hpp"


MapScreen::MapScreen(SDL_Renderer* renderer, Hero* hero, int* items)
{
	srand(time(NULL));

	this->renderer = renderer;
	this->hero = hero;
	this->items = items;

	//loop through map using nested loop and clear all values out to be zero(walls)
	for (int x = 0; x <= 9; x++)
	{
		for (int y = 0; y <= 9; y++)
		{
			map[x][y] = 0;
		}
		
	}

	//Open map text file
	fstream mapFile("../assets/map.txt");
	if (mapFile.is_open())
	{
		for (int y = 0; y <= 9; y++)
		{
			for (int x = 0; x <= 9; x++)
			{
				char grid;
				mapFile >> grid;
				if (grid == '0')
				{
					map[x][y] = 0; //wall
				}
				else
				{
					map[x][y] = 1;//land

					if (grid == 'h')
					{
						heroObj.type = 1;
						heroObj.x = x;
						heroObj.y = y;
					}
					else if (grid == 'd')
					{
						door.type = 2;
						door.x = x;
						door.y = y;
					}
					else if (grid == 'c')
					{
						MapObject chest;
						chest.type = 5;
						chest.x = x;
						chest.y = y;

						mapObjects.push_back(chest);
					}
					else if (grid == 'g')
					{
						MapObject glob;
						glob.type = 3;
						glob.x = x;
						glob.y = y;

						mapObjects.push_back(glob);
					}
					else if (grid == 'm')
					{
						MapObject mimic;
						mimic.type = 4;
						mimic.x = x;
						mimic.y = y;

						mapObjects.push_back(mimic);
					}
				}
			}
		}
	}
	//close file
	mapFile.close();

	//LOAD UP TILE TEXTURES
	heroTexture = IMG_LoadTexture(renderer, "../assets/girlTile.png");
	doorTexture = IMG_LoadTexture(renderer, "../assets/doorTile.png");
	globTexture = IMG_LoadTexture(renderer, "../assets/globTile.png");
	chestTexture = IMG_LoadTexture(renderer, "../assets/chestTile.png");

	//setup info box
	infoBox.setup(renderer);
	infoBox.setText("Welcome to the Dungeon!");
}


MapScreen::~MapScreen()
{
	//CLEANUP TEXTURE MEMORY
	SDL_DestroyTexture(heroTexture);
	SDL_DestroyTexture(doorTexture);
	SDL_DestroyTexture(globTexture);
	SDL_DestroyTexture(chestTexture);
}

void MapScreen::itemFound()
{
	//randomly pick an item (between 1-4)
	int item = rand() % 4 + 1;

	bool freeSlotFound = false;
	for (int i = 0; i < 10; i++)
	{
		if (items[i] == 0)
		{
			freeSlotFound = true;
			items[i] = item;
			break;
		}
	}

	if (freeSlotFound)
	{
		if (item == 1)
			infoBox.setText("Found chocolate!");
		else if (item ==2)
			infoBox.setText("Found grenade!");
		else if (item == 3)
			infoBox.setText("Found ATK Boost!");
		else if (item == 4)
			infoBox.setText("Found DEF Boost!");
	}
	else
	{
		infoBox.setText("You're bag is full!");
	}
	infoBox.visible = true;


}

void MapScreen::update()
{
	SDL_Event sdlEvent;
	
	while(SDL_PollEvent(&sdlEvent))
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
			//hide infobox when space is pressed
			if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				infoBox.visible = false;
			}

			
			if (infoBox.visible == false && hero->getHP() > 0)
			{
				//player movement
				int hx = heroObj.x;
				int hy = heroObj.y;
				//right dpad on keyboard
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					hx++;
				}
				//left
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT)
				{
					hx--;
				}
				//down dpad on keyboard
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					hy++;
				}
				//left
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP)
				{
					hy--;
				}
				//if hx and hy are within the grid
				//AND is land we can walk on (map value of 1)
				if (hx >= 0 && hx <= 9 && hy >= 0 && hy <= 9 && map[hx][hy] == 1)
				{
					//set heroObj.x and y to hx and hy
					heroObj.x = hx;
					heroObj.y = hy;

					//can we escape the dungeon?
					if (!doorLocked && !escaped && heroObj.x == door.x && heroObj.y == door.y)
					{
						infoBox.setText("You escaped!");
						infoBox.visible = true;
						escaped = true;
					}

					//see if we walked onto a map object
					for (list<MapObject>::iterator mo = mapObjects.begin(); mo != mapObjects.end(); mo++)
					{
					
						if ((*mo).active)
						{
							//is hero's x,y overlapping this mapobjects x,y
							if (heroObj.x == mo->x && heroObj.y == mo->y)
							{
								mo->active = false;

								//check map objects type and deal with accordingly
								if (mo->type == 3)
								{
									BattleScreen battle(renderer, hero, items, globType);
									battle.update();

									if (battle.quit)
										quit = true;
									else if (hero->getHP() <= 0)
									{
										infoBox.setText("You died!");
										infoBox.visible = true;
									}
								}
								else if (mo->type == 4)
								{
									BattleScreen battle(renderer, hero, items, mimicType);
									battle.update();

									if (battle.quit)
										quit = true;
									else if (hero->getHP() <= 0)
									{
										infoBox.setText("You died!");
										infoBox.visible = true;
									}
								}
								else if (mo->type == 5)
								{
									//open chest get item 
									itemFound();
								}
							}
						}
					}
				}
				else
				{
					//invalid move, dont need to do anything here
				}
			}
		}
	}

	//check to see if map objects all inactive and if we should unlock the door
	if (!infoBox.visible && doorLocked)
	{
		bool monstersAlive = false;
		for (MapObject mo : mapObjects)
		{
			//if is a monster(glob or mimic)
			if (mo.type == 3 || mo.type == 4)
			{
				//if is active monster?
				if (mo.active)
				{
					monstersAlive = true;
					break;
				}
			}
		}
		//if all monsters are dead, unlock the door
		if (!monstersAlive)
		{
			doorLocked = false;
			infoBox.setText("The door is unlocked!");
			infoBox.visible = true;
		}
	}

	//has user closed infobox after escaping
	if (!infoBox.visible && (escaped || hero->getHP() <= 0))
	{
		quit = true;
	}

}

void MapScreen::draw() {
	//MAP DRAWING
	SDL_Rect tileRect = { 0,0,32,32 };
	//loop through and draw each grid value from map array
	for (int x = 0; x <= 9; x++)
	{
		for (int y = 0; y <= 9; y++)
		{
			//IF is ground, set draw colour to ground colour
			//ELSE set to wall colour
			if (map[x][y] == 1)
			{
				//ground
				SDL_SetRenderDrawColor(renderer, 136, 60, 100, 255);
			}
			else
			{
				//walls
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}
			//MOVE rectangle to grid position with regards to tile width/height
			tileRect.x = x*tileRect.w;
			tileRect.y = y*tileRect.h;
			//draw rectangle to screen using current draw colour
			SDL_RenderFillRect(renderer, &tileRect);
		}
	}

	//DRAW MAP OBJECTS
	//draw hero
	tileRect.x = heroObj.x * tileRect.w; 
	tileRect.y = heroObj.y * tileRect.h;
	SDL_RenderCopy(renderer, heroTexture, NULL, &tileRect);
	//draw door
	tileRect.x = door.x * tileRect.w; 
	tileRect.y = door.y * tileRect.h;
	SDL_RenderCopy(renderer, doorTexture, NULL, &tileRect);
	//DRAW MAP OBJECTS IN LIST
	for (MapObject mo : mapObjects)
	{
		if (mo.active)
		{
			tileRect.x = mo.x * tileRect.w;
			tileRect.y = mo.y * tileRect.h;
			if (mo.type == 3)//glob
			{
				SDL_RenderCopy(renderer, globTexture, NULL, &tileRect);
			}
			else//mimic or chest
			{
				SDL_RenderCopy(renderer, chestTexture, NULL, &tileRect);
			}
		}
	}

	//draw info box on top
	infoBox.draw();
}