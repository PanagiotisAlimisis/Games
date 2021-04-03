#include "GameObject.hpp"


GameObject::GameObject()
{
    position = new Vector2D(0, 0);
    velocity = new Vector2D(0, 0);
}


void GameObject::load(int x, int y, int w, int h, std::string textureId)
{
    position->setX(x);
    position->setY(y);

    this->width = w;
    height = h;
    this->textureId = textureId;
}


void GameObject::draw(SDL_Renderer *renderer)
{
    TextureManager::Instance()->draw(textureId, *position, width, height, renderer);
}


void GameObject::update()
{   
}


void GameObject::clean()
{

}