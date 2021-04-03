#include "Paddle.hpp"


Paddle::Paddle()
{
    velocity->setY(10);
}


void Paddle::load(int x, int y, int w, int h, std::string textureId)
{
    GameObject::load(x, y, w, h, textureId);
}


void Paddle::draw(SDL_Renderer *renderer)
{
    GameObject::draw(renderer);
}


void Paddle::moveUp()
{
    int newYPos = position->getY() - velocity->getY(); 
    if (newYPos < 0)
    {
        newYPos = 0;
    } 
    position->setY(newYPos);
}


void Paddle::moveDown()
{
    int newYPos = velocity->getY() + position->getY();
    if (newYPos > 720 - 90)
    {
        newYPos = 720 - 90;
    } 
    position->setY(newYPos);
}


void Paddle::clean()
{

}


void Paddle::update()
{
    
}


Vector2D Paddle::getPaddle()
{
    return *position;
}


int Paddle::getHeight()
{
    return height;
}


int Paddle::getWidth()
{
    return width;
}