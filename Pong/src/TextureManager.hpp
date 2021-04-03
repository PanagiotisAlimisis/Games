#ifndef _TEXTUREMANAGER_HPP
#define _TEXTUREMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include "Vector2D.hpp"

class TextureManager
{
private:
    /*Singleton class.*/
    TextureManager() {}
    static TextureManager *instance;

    /*Associate each texture with a unique id*/
    std::map<std::string, SDL_Texture *> textureMap;

    
public:
    /**
     * @brief Load a texture
     * @param filename File to load
     * @param id Unique ID associated with the texture
     * @param renderer Renderer
     * @return True if loading was succesfull, false otherwise
     */
    bool loadTexture(std::string filename, std::string id, SDL_Renderer *renderer);

    /**
     * @brief Draw the texture associated with id
     * @param id Unique ID
     * @param x X on X-Y axis
     * @param y Y on X-Y axis
     * @param w Width of the texture
     * @param h Height of the texture
     * @param renedrer Renderer
     */
    void draw(std::string id, Vector2D &position, int w, int h, SDL_Renderer *renderer);


    static TextureManager *Instance()
    {   
        if (instance == 0)
        {
            instance = new TextureManager();
        }
        return instance;
    }

};

typedef TextureManager TheTextureManager;


#endif