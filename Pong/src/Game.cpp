#include "Game.hpp"


bool Game::init(const char *title, int x, int y, int w, int h, int flags) 
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout << SDL_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow(title, x, y, w, h, flags);
    if (window == nullptr)
    {
        cout << SDL_GetError() << endl;
        return false;    
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        cout << SDL_GetError() << endl;
        return false;        
    }

    // SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_Surface* surface = IMG_Load("resources/background.png");
    if (surface == 0)
    {
        return false;
    }

    background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    

    paddleLeft = new Paddle();
    paddleRight = new Paddle();
    ball = new Ball();
    
    gameObjects.push_back(paddleLeft);
    gameObjects.push_back(paddleRight);
    gameObjects.push_back(ball);

    paddleLeft->load(50, 290, 10, 90, "paddle1");
    paddleRight->load(1230, 290, 10, 90, "paddle2");
    ball->load(640, 300, 10, 10, "ball");

    /*load objects*/
    if (!TextureManager::Instance()->loadTexture("resources/paddle.png", "paddle1", renderer))
    {
        return false;
    }
    if (!TextureManager::Instance()->loadTexture("resources/paddle.png", "paddle2", renderer))
    {
        return false;
    }
    if (!TextureManager::Instance()->loadTexture("resources/ball.png", "ball", renderer))
    {
        return false;
    }

    /*Load font*/
    if (!FontManager::Instance()->loadFont("resources/font.ttf", "font"))
    {
        return false;
    }
    
    /*Load audio*/
    if (!Audio::Instance()->load("resources/hit.wav", "hit", SOUND_SFX))
    {
        return false;
    }

    runs = true;
    start = false;
    scoreLeft = scoreRight = 0;
    return true;
}    
    
    
void Game::update()
{   
    for (std::vector<GameObject*>::size_type i=0; i!=gameObjects.size(); ++i)
    {
        if (!start && gameObjects[i] == ball)
        {
            continue;
        }
        gameObjects[i]->update();
    }
    
    if (ball->collisionWithLeftPaddle(*paddleLeft))
    {
        Audio::Instance()->playSound("hit", 1);
    }

    if (ball->collisionWithRightPaddle(*paddleRight))
    {
        Audio::Instance()->playSound("hit", 1);    
    }
    
    int ballIsOut = ball->isOut();
    if (ballIsOut < 0)
    {
        ++scoreRight;
        ball->startAgain();
        start = false; 
    }
    if (ballIsOut > 1280)
    {
        ++scoreLeft;
        ball->startAgain();
        start = false;
    }
    
}


void Game::handleEvents()
{
    /*simultaneously movement of the two paddles*/
    paddleLeft->keystate = SDL_GetKeyboardState(0);
    paddleRight->keystate = SDL_GetKeyboardState(0);
    
    if (paddleLeft->keystate[SDL_SCANCODE_W]) {
        paddleLeft->moveUp();
    }
    if (paddleLeft->keystate[SDL_SCANCODE_S]) {
        paddleLeft->moveDown();
    }
    if (paddleRight->keystate[SDL_SCANCODE_UP]) {
        paddleRight->moveUp();
    }
    if (paddleRight->keystate[SDL_SCANCODE_DOWN]) {
        paddleRight->moveDown();
    }

    while (SDL_PollEvent(&sdlEvent))
    {
        switch(sdlEvent.type)
        {
            case SDL_QUIT:
                runs = false;
                break;
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE)
                {
                    start = true;
                }
                else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_R)
                {
                    scoreLeft = scoreRight = 0;
                    start = true;
                }
                break;
            default:
                break;
        }
    }
}


void Game::render()
{
    SDL_RenderClear(renderer);  
    
    SDL_RenderCopy(renderer, background, NULL, NULL);
    if (!start)
    {
        FontManager::Instance()->draw("font", 290, 400, 700, 70, renderer, "PRESS SPACE TO START");    
        FontManager::Instance()->draw("font", 290, 480, 700, 70, renderer, "PRESS R TO RESTART");    
    }
    

    FontManager::Instance()->draw("font", 490, 20, 50, 50, renderer, std::to_string(scoreLeft).c_str());
    FontManager::Instance()->draw("font", 740, 20, 50, 50, renderer, std::to_string(scoreRight).c_str());
    
    for (std::vector<GameObject*>::size_type i = 0; i != gameObjects.size(); ++i)
    {
        gameObjects[i]->draw(renderer);
    }

    SDL_RenderPresent(renderer);
}


void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
}


Game::Game()
{

}


Game::~Game()
{

}
