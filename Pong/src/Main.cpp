#include <iostream>
#include "Game.hpp"

using namespace std;

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;


int main()
{
    uint32_t frameStart, frameTime;
    
    Game *game = new Game();
 
    game->init("PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!game)
    {
        cout << "Window initialization failed." << endl;   
    }
 
    while (game->isRunning())
    {
        frameStart = SDL_GetTicks();

        game->handleEvents(); 
        game->update();  
        game->render();   

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME)
        {
            SDL_Delay((int) (DELAY_TIME - frameTime));
        }
    }

    game->clean();

    return 0;
}