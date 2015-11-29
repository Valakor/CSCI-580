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
  //  mTree->buildEverGreen(2, Vector3(0.0f, -20.0f, 0.0f));
  //  mTree->buildGrass(Vector3(0.0f, 0.0f, 0.0f));
    mTree->buildTree(2, Vector3(110.0f, 0.0f, -50.0f));

	// Spawn a couple procedural mesh actors
//	RegenerateWorld();
//	mGame.GetInput().BindAction("Regenerate", InputEvent::IE_Pressed, this, &GameMode::RegenerateWorld);
}

void GameMode::RegenerateWorld()
{
	static size_t iterations = 0;
	static const size_t MAX_ITER = 5;
	static const size_t NUM_ICOS = 4;
	static const float RADIUS = 150.0f;

	for (auto actor : mProceduralActors)
	{
		actor->SetIsAlive(false);
	}
	mProceduralActors.clear();

	float angle = 0.0f;
	for (int i = 0; i < NUM_ICOS; ++i)
	{
		auto actor = Actor::Spawn(mGame);
		auto meshComp = MeshComponent::Create(*(actor.get()));
		auto procMesh = ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(iterations));
		meshComp->SetMesh(procMesh);
		actor->SetScale(30.f);
		actor->SetPosition(Vector3(RADIUS * Math::Cos(angle), RADIUS * Math::Sin(angle), 0.0f));
		mProceduralActors.push_back(actor);

		angle += Math::TwoPi / NUM_ICOS;
	}


	iterations = (iterations + 1) % MAX_ITER;

}

