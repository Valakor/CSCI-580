//
//  Planet.cpp
//  Game-mac
//
//  Created by Matthew Pohlmann on 11/29/15.
//

#include "Planet.h"
#include "Game.h"

IMPL_ACTOR(Planet, Actor);

Planet::Planet(Game& game) : Super(game)
{
	mCurrentIterations = -1;
    mMesh = MeshComponent::Create(*this);
	SetIcoIterations(0, -1);
	SetScale(200.f);
}

Planet::~Planet()
{
	Cleanup();
}

void Planet::SetIcoIterations(size_t iterations, int perlinSeed)
{
	if (iterations == mCurrentIterations) return;

	mCurrentIterations = iterations;
	mPerlinSeed = perlinSeed;

	Cleanup();
	Generate();
}

