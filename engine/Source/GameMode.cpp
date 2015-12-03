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
#include "Rock.h"
#include "Sky.h"
#include "PlanetTerra.h"
#include "PlanetRinged.h"

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
    
  	// Spawn ship
	mShip = Ship::Spawn( mGame );

    // Generate the ringed planet (moon)
	auto ringedPlanet = PlanetRinged::Spawn(mGame);
	ringedPlanet->SetPosition(Vector3(350.0f, 400.0f, 200.0f));
	ringedPlanet->SetScale(60.0f);
	ringedPlanet->SetRotation(Quaternion(Vector3::UnitX, Math::Pi / 4.0f));
	mPlanets.push_back(ringedPlanet);

	// Generate the terra planet (earth-like)
	auto planet = PlanetTerra::Spawn(mGame);
	planet->SetPosition(Vector3(450.0f, 0.0f, 0.0f));
	mPlanets.push_back(planet);

	RegenerateWorld(4);

	// Add generation input bindings
	mGame.GetInput().BindAction("Regenerate0", InputEvent::IE_Pressed, this, &GameMode::RegenerateLevel0);
	mGame.GetInput().BindAction("Regenerate1", InputEvent::IE_Pressed, this, &GameMode::RegenerateLevel1);
	mGame.GetInput().BindAction("Regenerate2", InputEvent::IE_Pressed, this, &GameMode::RegenerateLevel2);
	mGame.GetInput().BindAction("Regenerate3", InputEvent::IE_Pressed, this, &GameMode::RegenerateLevel3);
	mGame.GetInput().BindAction("Regenerate4", InputEvent::IE_Pressed, this, &GameMode::RegenerateLevel4);
	mGame.GetInput().BindAction("Regenerate5", InputEvent::IE_Pressed, this, &GameMode::RegenerateLevel5);
	mGame.GetInput().BindAction("Regenerate6", InputEvent::IE_Pressed, this, &GameMode::RegenerateLevel6);
	mGame.GetInput().BindAction("Regenerate7", InputEvent::IE_Pressed, this, &GameMode::RegenerateLevel7);

}

void GameMode::RegenerateWorld(int icoIterations)
{
	for (size_t i = 0; i < mPlanets.size(); ++i)
	{
		mPlanets[i]->SetIcoIterations(icoIterations, i);
    }
}

