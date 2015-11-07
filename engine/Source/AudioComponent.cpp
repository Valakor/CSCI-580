//
//  AudioComponent.cpp
//  Game-mac
//
//  Created by Matthew Pohlmann on 8/2/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "AudioComponent.h"
#include "Actor.h"
#include <SDL/SDL_mixer.h>

SoundCue::SoundCue() :
    mChannel(-1)
{
    
}

SoundCue::SoundCue(int channel) :
    mChannel(channel)
{
    
}

void SoundCue::Pause()
{
    if (mChannel == -1)
    {
        return;
    }
    
    Mix_Pause(mChannel);
}

void SoundCue::Resume()
{
    if (mChannel == -1)
    {
        return;
    }
    
    Mix_Resume(mChannel);
}

void SoundCue::Stop()
{
    if (mChannel == -1)
    {
        return;
    }

    Mix_HaltChannel(mChannel);
}

bool SoundCue::IsPlaying()
{
    if (mChannel == -1)
    {
        return false;
    }
    
    return Mix_Playing(mChannel) == 1;
}

bool SoundCue::IsPaused()
{
    if (mChannel == -1)
    {
        return false;
    }
    
    return Mix_Paused(mChannel) == 1;
}

IMPL_COMPONENT(AudioComponent, Component);

AudioComponent::AudioComponent(Actor& owner) : Super(owner)
{
    
}

SoundCue AudioComponent::PlaySound(SoundPtr sound, bool looping /* = false */)
{
    int channel = Mix_PlayChannel(-1, sound->GetData(), looping ? -1 : 0);
    return SoundCue(channel);
}
