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

IMPL_ACTOR(GameMode, Actor);

GameMode::GameMode(Game& game) : Super(game)
	, mHud(nullptr)
	, mShip(nullptr)
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
		auto asteroid = Asteroid::Spawn( mGame );
		asteroid->SetPosition( Random::GetVector( minVec, maxVec ) );
	}

	// Spawn ship
	mShip = Ship::Spawn( mGame );

	// Create a couple planets
	static const size_t NUM_PLANETS = 4;
	static const float RADIUS = 150.0f;
	float angle = 0.0f;
	for (int i = 0; i < NUM_PLANETS; ++i)
	{
		auto planet = Planet::Spawn(mGame);
		planet->SetPosition(Vector3(RADIUS * Math::Cos(angle), RADIUS * Math::Sin(angle), 0.0f));
		mPlanets.push_back(planet);

		angle += Math::TwoPi / NUM_PLANETS;
	}
	RegenerateWorld();
	mGame.GetInput().BindAction("Regenerate", InputEvent::IE_Pressed, this, &GameMode::RegenerateWorld);
}

void GameMode::RegenerateWorld()
{
	static size_t iterations = 0;
	static const size_t MAX_ITER = 5;

	for (auto planet : mPlanets)
	{
		planet->SetIcoIterations(iterations);
	}

	iterations = (iterations + 1) % MAX_ITER;
}

