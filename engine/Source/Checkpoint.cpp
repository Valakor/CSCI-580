//
//  Checkpoint.cpp
//  Game-windows
//
//  Created by Matthew Pohlmann on 11/5/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "Checkpoint.h"
#include "Game.h"
#include "MeshComponent.h"
#include "SphereCollision.h"

IMPL_ACTOR(Checkpoint, Actor);

Checkpoint::Checkpoint( Game& game ) : Super( game )
{
    auto mesh = MeshComponent::Create(*this);
    auto meshPtr = game.GetAssetCache().Load<Mesh>("Meshes/Checkpoint.itpmesh2");
    mesh->SetMesh(meshPtr);
    
	auto collider = SphereCollision::Create( *this );
	collider->RadiusFromMesh( meshPtr );
	collider->SetScale( 0.75f );
}

