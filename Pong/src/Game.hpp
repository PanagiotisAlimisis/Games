#ifndef _GAME_HPP
#define _GAME_HPP

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "TextureManager.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "FontManager.hpp"
#include "Audio.hpp"

using namespace std;

class Game
{
private:
    bool runs;
    bool start;

    SDL_Texture *background;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    SDL_Event sdlEvent;

    /*polymorphism*/
    /*This vector keeps all the objects of the game.*/
    std::vector<GameObject*> gameObjects;

    Paddle *paddleLeft;
    Paddle *paddleRight;
    Ball *ball;

    int scoreLeft;
    int scoreRight;
    
    Audio *audio;

public:

    Game();
    ~Game();

    /**
     * @brief Initialize the game window and the renderer.
     * @param title The title of the window
     * @param x X position of the window on the X-Y axis 
     * @param y Y position of the window on the X-Y axis
     * @param w Width of the window
     * @param h Height of the window
     * @param flags Flags for the window
     * @returns True if the window initialized, false if the window failed to get initialized 
     */
    bool init(const char *title, int x, int y, int w, int h, int flags);

    void update();
    void handleEvents();
    void render();
    void clean();

    bool isRunning() {return runs;}
};

#endif