//
//  Sound.cpp
//  Game-mac
//
//  Created by Matthew Pohlmann on 8/2/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "Sound.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

Sound::Sound() :
    mData(nullptr)
{
    
}

Sound::~Sound()
{
    if (mData != nullptr)
    {
        Mix_FreeChunk(mData);
    }
}

bool Sound::Load(const char* fileName, class AssetCache* cache)
{
    mData = Mix_LoadWAV(fileName);
    
    if (mData == nullptr)
    {
        SDL_Log("Failed to load Sound asset at: %s", fileName);
        return false;
    }
    
    return true;
}
