//
//  Rock.cpp
//  Game-mac
//
//  Created by Shazzy Gustafson on 11/29/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "Rock.h"
#include "Game.h"
#include "MeshComponent.h"


IMPL_ACTOR(Rock, Actor);

Rock::Rock(Game& game) : Super(game)
{
    auto mesh = MeshComponent::Create(*this);
    auto meshPtr = game.GetAssetCache().Load<Mesh>("Meshes/rock.itpmesh2");
    mesh->SetMesh(meshPtr);
    
    

}

