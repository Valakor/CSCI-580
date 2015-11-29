//
//  Tree.cpp
//  Game-mac
//
//  Created by Shazzy Gustafson on 11/19/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#include "Tree.h"
#include "Game.h"
#include "Mesh.h"
#include "CameraComponent.h"
#include "Checkpoint.h"
#include "ProceduralMesh.h"
#include "Foliage.h"
#include "IcoGenerator.h"

IMPL_ACTOR(Tree, Actor);

Tree::Tree(Game& game) : Super(game)
{
  


}

void Tree::buildTree(int lvl, Vector3 pos){
    
    auto actor = Actor::Spawn(mGame);
    auto meshComp = MeshComponent::Create(*(actor.get()));
    auto meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(1));
    meshComp->SetMesh(meshPtr);
    actor->SetPosition(Vector3(pos.x, pos.y, pos.z));
    actor->SetScale(30.0f);
    
    
    auto ico_actor = Actor::Spawn(mGame);
    auto ico_meshComp = MeshComponent::Create(*(ico_actor.get()));
    auto ico_meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(1));
    ico_meshComp->SetMesh(ico_meshPtr);
    ico_actor->SetPosition(Vector3(pos.x, pos.y, pos.z + 100.0f));
    ico_actor->SetScale(30.0f);
    
    
    
    if(lvl > 1) {
        auto actor2 = Actor::Spawn(mGame);
        auto meshComp2 = MeshComponent::Create(*(actor2.get()));
        auto meshPtr2 =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(1));
        meshComp2->SetMesh(meshPtr2);
        actor2->SetScale(18.0f);
        float deltaAngle = .7f;
        Vector3 rotationAxis = Vector3(0,1,0);
        Quaternion deltaRotation = Quaternion( rotationAxis, deltaAngle );
        actor2->SetRotation(deltaRotation);
        actor2->SetPosition(Vector3(pos.x, pos.y , pos.z + 50.0f));
        
        
        auto ico_actor = Actor::Spawn(mGame);
        auto ico_meshComp = MeshComponent::Create(*(ico_actor.get()));
        auto ico_meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(1));
        ico_meshComp->SetMesh(ico_meshPtr);
        ico_actor->SetPosition(Vector3(pos.x + 30.0f, pos.y , pos.z + 90.0f));
        ico_actor->SetScale(20.0f);
    }
}


void Tree::buildEverGreen(int lvl, Vector3 pos) {
    
    auto actor = Actor::Spawn(mGame);
    auto meshComp = MeshComponent::Create(*(actor.get()));
    auto meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(1));
    meshComp->SetMesh(meshPtr);
    actor->SetPosition(Vector3(pos.x, pos.y, pos.z));
    actor->SetScale(50.0f);
    
    
    auto actor2 = Actor::Spawn(mGame);
    auto meshComp2 = MeshComponent::Create(*(actor2.get()));
    auto meshPtr2 =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(2));
    meshComp2->SetMesh(meshPtr2);
    actor2->SetPosition(Vector3(pos.x, pos.y, pos.z + 50.0f));
    actor2->SetScale(20.0f);     
}

void Tree::buildFluffyTree(int lvl, Vector3 pos) {
    
    //Branch
    auto actor = Actor::Spawn(mGame);
    auto meshComp = MeshComponent::Create(*(actor.get()));
    auto meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(1));
    meshComp->SetMesh(meshPtr);
    actor->SetPosition(Vector3(pos.x, pos.y, pos.z));
    actor->SetScale(30.0f);

    
    std::vector<ActorPtr> mProceduralActors;
    
    for (int i = 0; i < lvl; ++i)
    {
        auto actor = Actor::Spawn(mGame);
        auto meshComp = MeshComponent::Create(*(actor.get()));
        auto procMesh = ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(1));
        meshComp->SetMesh(procMesh);
        actor->SetScale(50.f - i * 10.0f);
        mProceduralActors.push_back(actor);
    }
    
    for (int i = 0; i < lvl; ++i)
    {
        mProceduralActors[i]->SetPosition(Vector3(pos.x, pos.y, pos.z + 100.0f + 50.0f * i));
    }

    
}

void Tree::buildGrass(Vector3 pos) {
    auto actor = Actor::Spawn(mGame);
    auto meshComp = MeshComponent::Create(*(actor.get()));
    auto meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(3));
    meshComp->SetMesh(meshPtr);
    actor->SetPosition(Vector3(pos.x, pos.y, pos.z));
}







