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
#include "IcoGenerator.h"
#include "Foliage.h"
#include <cfloat>

IMPL_ACTOR(GameMode, Actor);

GameMode::GameMode(Game& game) : Super(game)
	, mHud(nullptr)
	, mShip(nullptr)
    , mTree(nullptr)
{
    mAudio = AudioComponent::Create(*this);
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
	//	auto asteroid = Asteroid::Spawn( mGame );
//		asteroid->SetPosition( Random::GetVector( minVec, maxVec ) );
	}

	// Spawn ship
	mShip = Ship::Spawn( mGame );
    
    mTree = Tree::Spawn( mGame );
    mTree->buildTree(2, 0);

	// Spawn a couple procedural mesh actors
//	RegenerateWorld();
//	mGame.GetInput().BindAction("Regenerate", InputEvent::IE_Pressed, this, &GameMode::RegenerateWorld);
}

void GameMode::RegenerateWorld()
{
	static size_t iterations = 0;

	for (auto actor : mProceduralActors)
	{
		actor->SetIsAlive(false);
	}
	mProceduralActors.clear();

	for (int i = 0; i < 4; ++i)
	{
		auto actor = Actor::Spawn(mGame);
		auto meshComp = MeshComponent::Create(*(actor.get()));
		auto procMesh = ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(iterations));
    //    auto procMesh = ProceduralMesh::StaticCreate(std::make_shared<Environment>());
		meshComp->SetMesh(procMesh);
		actor->SetScale(30.f);
		mProceduralActors.push_back(actor);
	}

    
	mProceduralActors[0]->SetPosition(Vector3(150.f, 0.f, 0.f));
	mProceduralActors[1]->SetPosition(Vector3(-150.f, 0.f, 0.f));
	mProceduralActors[2]->SetPosition(Vector3(0.f, 150.f, 0.f));
	mProceduralActors[3]->SetPosition(Vector3(0.f, -150.f, 0.f));
 
    
	iterations = (iterations + 1) % 4;
}

