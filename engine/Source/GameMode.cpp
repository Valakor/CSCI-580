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


    
  	// Spawn ship
	mShip = Ship::Spawn( mGame );

    

    
    addPlanetRing();
    
    
    mTree = Tree::Spawn( mGame );
  //  mTree->buildEverGreen(2, Vector3(0.0f, 0.0f, 0.0f));
    //mTree->buildGrass(Vector3(x * 8.0f, y * 8.0f, 0.0f));
  //  mTree->buildGrass(Vector3(0.0f, 0.0f, 0.0f));
  //  mTree->buildFluffyTree(7, Vector3(0.0f, 0.0f, 0.0f));
  //  mTree->buildTree(3, Vector3(0.0f, 0.0f, 0.0f));
 


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
	//RegenerateWorld();
	//mGame.GetInput().BindAction("Regenerate", InputEvent::IE_Pressed, this, &GameMode::RegenerateWorld);

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


void GameMode::addPlanetRing() {
    // Spawn Asteroids
    const int NUM_ROCKS = 200;
    
    for ( int i = 0; i < NUM_ROCKS; ++i )
    {
        auto Rock = Rock::Spawn( mGame );
        float s = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        Rock->SetScale(s * 10.0f);
        Rock->SetRotation(Random::GetRotation() );
        
        
        int a, b, c;
        float z;
        float LO = -10.0f;
        float HI =  10.0f;
        while( true )
        {
            a = rand() % 31 - 15;
            b = rand() % 31 - 15;
            c = a * a + b * b;
            //z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            z = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
            
            if( c >= 144 && c <= 225 ) break;
        }
        Rock->SetPosition(Vector3(a * 10.0f, b * 10.0f, z));
    }
    
    
     auto ico_actor = Actor::Spawn(mGame);
     auto ico_meshComp = MeshComponent::Create(*(ico_actor.get()));
     auto ico_meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(2, nullptr, "Textures/Rock.png"));
     ico_meshComp->SetMesh(ico_meshPtr);
     ico_actor->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
     ico_actor->SetScale(80.0f);
    
}

