#include <iostream> 
#include <string> 
#include "Puzzles.hpp"
#include "Character.hpp"
#include "Hero.hpp"
#include "Glob.hpp"
#include "Mimic.hpp"
#include "MapScreen.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

using namespace std;


int main(int argc,  char** argv) {
	Hero hero;
	hero.setName("Hero");
	hero.setupStats(50, 1, 1, 10);

	//Initialise SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		//if init not return 0, then initialisation failed
		cout << "SDL Init Error: " << SDL_GetError() << endl;
		exit(1);
	}
	//initialise subsystems we need e.g sdl image, mixer, ttf
	//TODO: look up C++ bitwise logic
	//image- being able to deal with other image types other then bmp. Also lets you play with surface pixel data
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		cout << "SDL IMG Init Error: " << IMG_GetError() << endl;
		exit(1);
	}
	//ttf - text to font, for rendering text to screen
	if (TTF_Init() != 0)
	{
		cout << "SDL TTF Init Error: " << TTF_GetError() << endl;
		exit(1);
	}
	//mixer- sound and music
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		cout << "SDL Mixer Init Error: " << Mix_GetError() << endl;
		exit(1);
	}

	SDL_Window* window = SDL_CreateWindow("RPG GAME!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		cout << "SDL window Error: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		cout << "SDL renderer Error: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
	}

	//the size gfx are at min, but then scale up to actual window size
	SDL_RenderSetLogicalSize(renderer, 320, 240);

	//load up image file and store as Texture inside of gfx card VRAM
	SDL_Texture* testImg = IMG_LoadTexture(renderer, "../assets/girlIdle.png");
	if (testImg == NULL)
	{
		cout << "Image did not load! " << IMG_GetError() << endl;
	}
	//ITEMS(using arrays...)
	//items as ints. 0 = no item, 1 = chocolate, 2 = grenade, 3 = atk up, 4 = def up
	//integer array holding 10 int variables
	int items[10];
	//loop through array using for loop and set each slot to = 0 (no item)
	for (int i = 0; i <= 9; i++)
	{
		//reference index using variable
		items[i] = 0;
	}
	//set first item slot(index 0) to be our int number representing a chocolate
	items[0] = 1;
	//items[1] = 1;
	//items[2] = 3;
	
	//setup mapscreen object
	MapScreen mapScreen(renderer, &hero, items);

	bool keepLooping = true;
	//Game Loop
	while (keepLooping)
	{
		SDL_SetRenderDrawColor(renderer, 21, 209, 249, 255);//RGB (e.g R = 0-255)
		//clear entire screen with current draw colour
		SDL_RenderClear(renderer);

		SDL_Rect rect;
		rect.x = 10;
		rect.y = 10;
		rect.w = 50;
		rect.h = 50;
		SDL_SetRenderDrawColor(renderer, 34, 76, 22, 255);
		//draws filled in rectangle to window using rectangles data
		SDL_RenderFillRect(renderer, &rect);

		//the region of the texture we want to draw from
		SDL_Rect srcRect;
		srcRect.x = 20;
		srcRect.y = 50;
		srcRect.w = 55;
		srcRect.h = 75;

		//texture destination rectangle
		SDL_Rect destRect;
		destRect.x = 70;
		destRect.y = 20;
		destRect.w = 700;
		destRect.h = 137;


		//renderCopy renders textures to the window
		SDL_RenderCopy(renderer, testImg, &srcRect, &destRect);

		//update mapscreen
		mapScreen.update();

		if (mapScreen.quit)
			keepLooping = false;
		//draw game world
		mapScreen.draw();

		//swaps drawing buffer
		SDL_RenderPresent(renderer);

		//ticks are milliseconds since the start of SDL init
		//if (SDL_GetTicks() > 5000)//1000ms = 1second
		//{
		//	keepLooping = false;
		//}
		
	}
	//CLEANUP
	SDL_DestroyTexture(testImg);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();


	return 0;
}