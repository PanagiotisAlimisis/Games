#include "TextureManager.hpp"


TextureManager* TextureManager::instance = 0;

bool TextureManager::loadTexture(std::string filename, std::string id, SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load(filename.c_str());
    if (surface == 0)
    { 
        return false;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    /*if everything went ok put texture into map*/
    if (texture != 0)
    {
        textureMap[id] = texture;
        return true;
    }

    return false;
}


void TextureManager::draw(std::string id, Vector2D &position, int w, int h, SDL_Renderer *renderer)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = w;
    srcRect.h = destRect.h = h;
    destRect.x = position.getX();
    destRect.y = position.getY();

    SDL_RenderCopy(renderer, textureMap[id], &srcRect, &destRect);
}


