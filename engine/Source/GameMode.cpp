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
#include "MeshComponent.h"
#include "ProceduralMesh.h"
#include <cfloat>

IMPL_ACTOR(GameMode, Actor);

GameMode::GameMode(Game& game) : Super(game)
	, mHud(nullptr)
	, mShip(nullptr)
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

	// TESTING
	// Spawn a couple procedural mesh actors
	std::vector<ActorPtr> actors;
	for (int i = 0; i < 4; ++i)
	{
		auto actor = Actor::Spawn(mGame);
		auto meshComp = MeshComponent::Create(*(actor.get()));
		auto procMesh = ProceduralMesh::StaticCreate(MeshGenerator());
		meshComp->SetMesh(procMesh);
		actor->SetScale(20.f);
		actors.push_back(actor);
	}
	actors[0]->SetPosition(Vector3(150.f, 0.f, 0.f));
	actors[1]->SetPosition(Vector3(-150.f, 0.f, 0.f));
	actors[2]->SetPosition(Vector3(0.f, 150.f, 0.f));
	actors[3]->SetPosition(Vector3(0.f, -150.f, 0.f));
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

void GameMode::GameOver()
{
	bIsGameOver = true;
	mHud->SetStatusText( "Game Over!" );
}

