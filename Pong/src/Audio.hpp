#ifndef _AUDIO_HPP
#define _AUDIO_HPP

#include <string>
#include <map>
#include <iostream>
#include <SDL2/SDL_mixer.h>


enum soundType
{
    SOUND_MUSIC = 0,
    SOUND_SFX = 1
};


class Audio
{
public:
    static Audio *Instance()
    {
        if (instance == 0)
        {
            instance = new Audio();
        }
        return instance;
    }

    bool load(std::string filename, std::string id, soundType type);

    void playSound(std::string id, int loop);

    void playMusic(std::string id, int loop);
private:
    static Audio *instance;

    std::map<std::string, Mix_Chunk*> mapSfx;
    std::map<std::string, Mix_Music*> mapMusic;

    Audio();
    ~Audio();

    Audio(const Audio&); 
    Audio &operator=(const Audio&);
};

typedef Audio TheAudio;

#endif