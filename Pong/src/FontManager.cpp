#include "FontManager.hpp"

FontManager* FontManager::instance = 0;


bool FontManager::loadFont(std::string filename, std::string id)
{
    TTF_Font *tempFont = TTF_OpenFont(filename.c_str(), size);
    if (tempFont == nullptr)
    {   
        return false;
    }

    fontMap[id] = tempFont;
    return true;
}


void FontManager::draw(std::string id, int x, int y, int w, int h, SDL_Renderer *renderer, const char *text)
{
    SDL_Color textColor = { 255, 255, 255, 255 };

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(fontMap[id], text, textColor); 

    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 

    SDL_Rect messageRect; 
    messageRect.x = x; 
    messageRect.y = y; 
    messageRect.w = w;  
    messageRect.h = h; 

    SDL_RenderCopy(renderer, message, NULL, &messageRect); 
    
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}
