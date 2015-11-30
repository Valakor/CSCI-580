//
//  Planet.cpp
//  Game-mac
//
//  Created by Matthew Pohlmann on 11/29/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "Planet.h"
#include "Game.h"
#include "ProceduralMesh.h"
#include "IcoGenerator.h"

IMPL_ACTOR(Planet, Actor);

Planet::Planet(Game& game) : Super(game)
{
	mCurrentIterations = -1;
    mMesh = MeshComponent::Create(*this);
	SetIcoIterations(mCurrentIterations);
	SetScale(30.f);
}

void Planet::SetIcoIterations(size_t iterations)
{
	if (iterations == mCurrentIterations) return;

	mCurrentIterations = iterations;
	auto meshPtr = ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(iterations));
	mMesh->SetMesh(meshPtr);
}

