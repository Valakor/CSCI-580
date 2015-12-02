//
//  Sky.cpp
//  Game-mac
//
//  Created by Shazzy Gustafson on 11/29/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#include "Sky.h"
#include "Game.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "Random.h"
#include "IcoGenerator.h"

IMPL_ACTOR(Sky, Actor);

Sky::Sky(Game& game) : Super(game)
{

    

}


void Sky::addClouds(Vector3 pos) {
    
    auto actor = Actor::Spawn(mGame);
    auto mesh = MeshComponent::Create(*(actor.get()));
    auto procMesh = ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(1, nullptr, "Textures/Cloud.png"));
    mesh->SetMesh(procMesh);
    
    // auto movement = MoveComponent::Create(*this, Component::PreTick);
    //  movement->SetLinearSpeed(10.0f);
    // movement->SetLinearAxis(-1.0f);
    
    //  actor->SetRotation(Random::GetRotation());
    actor->SetScale( 30.0f );
    actor->SetPosition(Vector3(pos.x, pos.y, pos.z));
    
    
    auto actor2 = Actor::Spawn(mGame);
    auto mesh2 = MeshComponent::Create(*(actor2.get()));
    auto procMesh2 = ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(1, nullptr, "Textures/Cloud.png"));
    mesh2->SetMesh(procMesh2);
    
    // auto movement = MoveComponent::Create(*this, Component::PreTick);
    //  movement->SetLinearSpeed(10.0f);
    // movement->SetLinearAxis(-1.0f);
    
    //   actor2->SetRotation(Random::GetRotation());
    actor2->SetScale( 20.0f );
    actor2->SetPosition(Vector3(pos.x, pos.y + 30.0f, pos.z -15.0f));
    
    auto actor3 = Actor::Spawn(mGame);
    auto mesh3 = MeshComponent::Create(*(actor3.get()));
    auto procMesh3 = ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(1, nullptr, "Textures/Cloud.png"));
    mesh3->SetMesh(procMesh3);
    
    // auto movement = MoveComponent::Create(*this, Component::PreTick);
    //  movement->SetLinearSpeed(10.0f);
    // movement->SetLinearAxis(-1.0f);
    
    //actor3->SetRotation(Random::GetRotation());
    actor3->SetScale( 20.0f );
    actor3->SetPosition(Vector3(pos.x, pos.y - 30.0f, pos.z-15.0f));
    
}


