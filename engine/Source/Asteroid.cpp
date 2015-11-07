//
//  Asteroid.cpp
//  Game-mac
//
//  Created by Matthew Pohlmann on 8/1/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "Asteroid.h"
#include "Game.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "Random.h"

IMPL_ACTOR(Asteroid, Actor);

Asteroid::Asteroid(Game& game) : Super(game)
{
    auto mesh = MeshComponent::Create(*this);
    auto meshPtr = game.GetAssetCache().Load<Mesh>("Meshes/AsteroidMesh.itpmesh2");
    mesh->SetMesh(meshPtr);
    
    auto movement = MoveComponent::Create(*this, Component::PreTick);
    movement->SetLinearSpeed(150.0f);
    movement->SetLinearAxis(1.0f);
    
    SetRotation(Random::GetRotation());
	SetScale( 0.1f );
}

