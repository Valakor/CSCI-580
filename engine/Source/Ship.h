//
//  Ship.h
//  Game-mac
//
//  Created by Matthew Pohlmann on 8/2/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "Actor.h"
#include "InputComponent.h"
#include "Texture.h"
#include "MeshComponent.h"
#include "AudioComponent.h"
#include "CameraComponent.h"

class Ship : public Actor
{
    DECL_ACTOR(Ship, Actor);
    
    InputComponentPtr mInput;
    
    MeshComponentPtr mMesh;
    
    AudioComponentPtr mAudio;
    SoundCue mEngineSoundCue;

	CameraComponentPtr mCamera;
    
public:
    
    Ship(class Game& game);
    
    virtual void BeginPlay() override;
    virtual void Tick(float deltaTime) override;

	void Recenter();
    
};

DECL_PTR(Ship);
