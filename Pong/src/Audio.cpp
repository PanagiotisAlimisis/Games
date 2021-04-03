#include "Audio.hpp"

TheAudio* Audio::instance = 0;


Audio::Audio()
{
    Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
}


bool Audio::load(std::string filename, std::string id, soundType type)
{
    if (type == SOUND_MUSIC)
    {
        Mix_Music *music = Mix_LoadMUS(filename.c_str());
        if (music == 0)
        {
            std::cout << SDL_GetError() << std::endl;
            return false;
        }
        mapMusic[id] = music;
        return true;
    }
    else if (type == SOUND_SFX)
    {
        Mix_Chunk *chunk = Mix_LoadWAV(filename.c_str());
        if (chunk == 0)
        {
            std::cout << SDL_GetError() << std::endl;
            return false;
        }
        mapSfx[id] = chunk;
        return true;
    }

    return false;
}


void Audio::playSound(std::string id, int loop)
{
    Mix_PlayChannel(-1, mapSfx[id], loop);
}


void Audio::playMusic(std::string id, int loop)
{
    Mix_PlayMusic(mapMusic[id], loop);
}


Audio::~Audio()
{
    Mix_CloseAudio();
}
