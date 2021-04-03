#ifndef _PADDLE_HPP
#define _PADDLE_HPP

#include "GameObject.hpp"

class Paddle : public GameObject
{
public:    
    const uint8_t* keystate;

    Paddle();

    Vector2D getPaddle();

    int getHeight();

    int getWidth();

    void load(int x, int y, int w, int h, std::string textureId);

    void draw(SDL_Renderer *renderer);

    void update();

    void moveUp();

    void moveDown();

    void clean();

};

#endif