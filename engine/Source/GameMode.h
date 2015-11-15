//
//  GameMode.h
//  Game-mac
//
//  Created by Matthew Pohlmann on 8/8/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "AudioComponent.h"
#include "HUD.h"
#include "Ship.h"
#include "GameTimers.h"

class GameMode : public Actor
{
    DECL_ACTOR(GameMode, Actor);
public:
    GameMode(Game& game);
    
    virtual void BeginPlay() override;

private:

	std::vector<ActorPtr> mProceduralActors;
	void RegenerateWorld();
    
    AudioComponentPtr mAudio;

    HUDPtr mHud;

	ShipPtr mShip;
};

DECL_PTR(GameMode);
