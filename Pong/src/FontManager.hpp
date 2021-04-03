#ifndef _FONTMANAGER_HPP
#define _FONTMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>
#include "Vector2D.hpp"

class FontManager
{
private:
    /*Singleton class.*/
    FontManager() {if (TTF_Init() == -1) {std::cout << SDL_GetError() << std::endl;}}
    static FontManager *instance;

    /*Associate each texture with a unique id*/
    std::map<std::string, TTF_Font*> fontMap;
    int size = 10;
    
public:
    /**
     * @brief Load a font
     * @param filename File to load
     * @param id Unique ID associated with the font
     * @return True if loading was succesfull, false otherwise
     */
    bool loadFont(std::string filename, std::string id);

    /**
     * @brief Draw the font associated with id
     * @param id Unique ID
     * @param x X on X-Y axis
     * @param y Y on X-Y axis
     * @param w Width of the font
     * @param h Height of the font
     * @param renedrer Renderer
     */
    void draw(std::string id, int x, int y, int w, int h, SDL_Renderer *renderer, const char * text);


    static FontManager *Instance()
    {   
        if (instance == 0)
        {
            instance = new FontManager();
        }
        return instance;
    }

};

typedef FontManager TheFontManager;


#endif