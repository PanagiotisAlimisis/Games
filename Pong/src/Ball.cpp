#include "Ball.hpp"


Ball::Ball()
{
    int velo = 5 + rand() % 5;
    velocity->setX(velo);
    velocity->setY(0);
}


void Ball::load(int x, int y, int w, int h, std::string textureId)
{
    GameObject::load(x, y, w, h, textureId);
}


void Ball::draw(SDL_Renderer *renderer)
{
    GameObject::draw(renderer);
}


void Ball::update()
{
    /*Collision with the walls*/
    if (position->getY() + height >= 720 )
    {
        velocity->setY(-velocity->getY());
    }
    
    if (position->getY() <= 0 )
    {
        velocity->setY(-velocity->getY());
    }

    *position += *velocity;
}


bool Ball::collisionWithLeftPaddle(Paddle &paddle)
{
    if (collision(paddle))
    {   
        if (position->getX() <= paddle.getPaddle().getX() + paddle.getWidth()) 
        {
            velocity->setX(-velocity->getX());

            /*Ball on top of the paddle goes up.*/
            if (position->getY() < paddle.getPaddle().getY() + paddle.getHeight()/2-10)
            {
                velocity->setY(-(abs(velocity->getY())+ 3 + rand() % 5));
            }   /*Ball on bottom*/
            else if (position->getY() > paddle.getPaddle().getY() + paddle.getHeight()/2+10)
            {
                velocity->setY(abs(velocity->getY()) + 3 + rand() % 5);                
            } /*Ball on middle*/
            else 
            {
                velocity->setY(0);                 
                velocity->setX(8);                    
            }
        }
        return true;
    }
    return false;
}


bool Ball::collisionWithRightPaddle(Paddle &paddle)
{
    if (collision(paddle))
    {   
        if (position->getX() + width >= paddle.getPaddle().getX())
        {
            velocity->setX(-velocity->getX());
            
                      /*Ball on top of the paddle goes up.*/
            if (position->getY() < paddle.getPaddle().getY() + paddle.getHeight()/2-10)
            {
                velocity->setY(-(abs(velocity->getY())+ 3 + rand() % 5));
            }   /*Ball on bottom*/
            else if (position->getY() > paddle.getPaddle().getY() + paddle.getHeight()/2+10)
            {
                velocity->setY(abs(velocity->getY()) + 3 + rand() % 5);                
            } /*Ball on middle*/
            else 
            {
                velocity->setY(0);                 
                velocity->setX(-8);                    
            }
        }
        return true;
    }
    return false;
}


int Ball::isOut()
{
    return position->getX();
}


void Ball::startAgain()
{
    position->setX(640);
    position->setY(320);

    int velo = 5 + rand() % 5;
    int whosTurn = rand() % 2;
    if (whosTurn == 0)
    {
        velocity->setX(velo);
    }   
    else 
    {    
        velocity->setX(-velo);
    }
    velocity->setY(0);
}


void Ball::clean()
{

}


bool Ball::collision(Paddle &paddle)
{
    if(position->getY() >= paddle.getPaddle().getY() + paddle.getHeight())
    {
        return false;
    }
    if(position->getX() >= paddle.getPaddle().getX() + paddle.getWidth())
    {
        return false;
    }
    if(position->getY() + height <= paddle.getPaddle().getY())
    {
        return false;
    }
    if(position->getX() + width <= paddle.getPaddle().getX())
    {
        return false;
    }
    return true;
}