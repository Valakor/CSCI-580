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
#include "Arrow.h"
#include "GameTimers.h"

class GameMode : public Actor
{
    DECL_ACTOR(GameMode, Actor);
public:
    GameMode(Game& game);
    
    virtual void BeginPlay() override;
	virtual void Tick( float deltaTime ) override;

	bool CheckpointReached();
    
private:

	void SpawnRandomCheckpoint();
	void GameOver();
    
    AudioComponentPtr mAudio;
    SoundPtr mCheckpointReachedSound;

    HUDPtr mHud;

	ShipPtr mShip;
	ArrowPtr mArrow;

	TimerHandle mGameTimer;

	int mScore;
	bool bIsGameOver;
};

DECL_PTR(GameMode);
