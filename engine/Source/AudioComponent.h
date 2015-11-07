//
//  AudioComponent.h
//  Game-mac
//
//  Created by Matthew Pohlmann on 8/2/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "Component.h"
#include "Sound.h"

class SoundCue
{
private:
    int mChannel;
    
public:
    SoundCue();
    SoundCue(int channel);
    
    void Pause();
    void Resume();
    void Stop();
    
    bool IsPlaying();
    bool IsPaused();
};

class AudioComponent : public Component
{
    DECL_COMPONENT(AudioComponent, Component);
    
public:
    
    AudioComponent(Actor& owner);
    
    SoundCue PlaySound(SoundPtr sound, bool looping = false);
    
};

DECL_PTR(AudioComponent);

