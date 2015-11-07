//
//  GameMode.cpp
//  Game-mac
//
//  Created by Matthew Pohlmann on 8/8/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "GameMode.h"
#include "Game.h"
#include "Asteroid.h"
#include "Random.h"
#include "Checkpoint.h"
#include <cfloat>

IMPL_ACTOR(GameMode, Actor);

GameMode::GameMode(Game& game) : Super(game)
	, mHud(nullptr)
	, mShip(nullptr)
	, mArrow(nullptr)
	, mScore(0)
	, bIsGameOver(false)
{
    mAudio = AudioComponent::Create(*this);
	mCheckpointReachedSound = game.GetAssetCache().Load<Sound>( "Sounds/Checkpoint.wav" );
}

void GameMode::BeginPlay()
{
    Super::BeginPlay();
    
	// Spawn HUD
    mHud = HUD::Spawn( mGame );
    mHud->SetStatusText("Go!!!", 2.0f);

	// Spawn Asteroids
	const int NUM_ASTEROIDS = 500;
	const Vector3 minVec( -5000.f, -5000.f, -5000.f );
	const Vector3 maxVec( 5000.f, 5000.f, 5000.f );

	for ( int i = 0; i < NUM_ASTEROIDS; ++i )
	{
		auto asteroid = Asteroid::Spawn( mGame );
		asteroid->SetPosition( Random::GetVector( minVec, maxVec ) );
	}

	// Spawn ship
	mShip = Ship::Spawn( mGame );

	// Spawn waypoint arrow
	mArrow = Arrow::Spawn( mGame );
	mArrow->SetPlayer( mShip );

	// Spawn first checkpoint
	SpawnRandomCheckpoint();

	// Start game timer
	mGame.GetGameTimers().SetTimer( mGameTimer, this, &GameMode::GameOver, 15.0f, false );
}

void GameMode::Tick( float deltaTime )
{
	Super::Tick( deltaTime );

	if ( !bIsGameOver )
	{
		float remainingTime = mGame.GetGameTimers().GetRemainingTime( mGameTimer );
		mHud->SetTime( static_cast<int>(remainingTime + 0.99f) );
	}
}

bool GameMode::CheckpointReached()
{
	if ( bIsGameOver )
	{
		return false;
	}

	mScore += 100;
	mHud->SetScore( mScore );

	mAudio->PlaySound( mCheckpointReachedSound );
	SpawnRandomCheckpoint();
	mGame.GetGameTimers().AddTime( mGameTimer, 5.0f );

	return true;
}

void GameMode::SpawnRandomCheckpoint()
{
	Vector3 shipPos = mShip->GetPosition();
	Vector3 maxPos = Vector3( shipPos.x + 1000, shipPos.y + 1000, shipPos.z + 1000 );
	Vector3 minPos = Vector3( shipPos.x - 1000, shipPos.y - 1000, shipPos.z - 1000 );
	Vector3 checkpointPos = Random::GetVector( minPos, maxPos );

	auto checkpoint = Checkpoint::Spawn( mGame );
	checkpoint->SetPosition( checkpointPos );
	mArrow->SetTarget( checkpointPos );
}

void GameMode::GameOver()
{
	bIsGameOver = true;
	mHud->SetStatusText( "Game Over!" );
}

