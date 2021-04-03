#ifndef _GAMEOBJECT_HPP
#define _GAMEOBJECT_HPP

#include <SDL2/SDL.h>
#include <string>
#include "TextureManager.hpp"
#include "Vector2D.hpp"


class GameObject
{
protected:
    int width, height;

    Vector2D *position;
    Vector2D *velocity;

    std::string textureId;
public:

    GameObject();

    virtual void load(int x, int y, int w, int h, std::string textureId);

    /**
     * @brief Draw game objects
     */
    virtual void draw(SDL_Renderer *renderer);

    /**
     * @brief Update game objects
     */ 
    virtual void update();

    /**
     * @brief Destroy game objects
     */ 
    virtual void clean();
};

#endif