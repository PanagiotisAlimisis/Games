#ifndef _BALL_HPP
#define _BALL_HPP

#include "GameObject.hpp"
#include "Paddle.hpp"
#include <stdlib.h>

enum class Contact
{
    Top, Middle, Bottom
};

class Ball : public GameObject
{
public:

    Ball();

    /**
     * @brief Check if collision with a paddle happened.
     * @param paddle A paddle.
     */
    bool collisionWithLeftPaddle(Paddle &paddle);

    /**
     * @brief Check if collision with a paddle happened.
     * @param paddle A paddle.
     */
    bool collisionWithRightPaddle(Paddle &paddle);

    /**
     * @brief Checks if the ball is out of bounds
     */ 
    int isOut();

    /**
     * @brief If ball was out then start it again.
     */ 
    void startAgain();

    void load(int x, int y, int w, int h, std::string textureId);

    /**
     * @brief Draw ball
     */
    void draw(SDL_Renderer *renderer);

    /**
     * @brief Update  ball
     */ 
    void update();

    /**
     * @brief Destroy ball 
     */ 
    void clean();

private:
    bool collision(Paddle &paddle);
};

#endif