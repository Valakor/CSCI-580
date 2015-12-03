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

ActorPtr Tree::buildTree(int lvl, Vector3 pos, Quaternion deltaRotation){
    
    auto actor = Actor::Spawn(Game::Get());
    auto meshComp = MeshComponent::Create(*(actor.get()));
    auto meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(1));
    meshComp->SetMesh(meshPtr);
    actor->SetPosition(Vector3(pos.x, pos.y, pos.z));
    actor->SetScale(5.0f);
    actor->SetRotation(deltaRotation);
    
    
    auto ico_actor = Actor::SpawnAttached(*actor);
    auto ico_meshComp = MeshComponent::Create(*(ico_actor.get()));
    auto ico_meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(1, nullptr, "Textures/Tree.png"));
    ico_meshComp->SetMesh(ico_meshPtr);
    ico_actor->SetPosition(Vector3(0.0f, 0.0f, 2.7f));
    ico_actor->SetScale(1.0f);
    
    
    
    if(lvl > 1) {
        auto actor2 = Actor::SpawnAttached(*actor);
        auto meshComp2 = MeshComponent::Create(*(actor2.get()));
        auto meshPtr2 =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(1));
        meshComp2->SetMesh(meshPtr2);
        actor2->SetScale(0.8f);
        float deltaAngle = .7f;
        Vector3 rotationAxis = Vector3(0,1,0);
        Quaternion deltaRotation2 = Quaternion( rotationAxis, deltaAngle );
        actor2->SetRotation(deltaRotation2);
        actor2->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
        
        
        auto ico_actor2 = Actor::SpawnAttached(*actor);
        auto ico_meshComp2 = MeshComponent::Create(*(ico_actor2.get()));
        auto ico_meshPtr2 =  ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(1, nullptr, "Textures/Tree.png"));
        ico_meshComp2->SetMesh(ico_meshPtr2);
        ico_actor2->SetPosition(Vector3(1.0f, 0.0f , 2.0f));
        ico_actor2->SetScale(0.5f);
    }
    
    if (lvl > 2) {
        auto actor2 = Actor::SpawnAttached(*actor);
        auto meshComp2 = MeshComponent::Create(*(actor2.get()));
        auto meshPtr2 =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(1));
        meshComp2->SetMesh(meshPtr2);
        actor2->SetScale(0.8f);
        float deltaAngle = -0.7f;
        Vector3 rotationAxis = Vector3(0,1,0);
        Quaternion deltaRotation = Quaternion( rotationAxis, deltaAngle );
        actor2->SetRotation(deltaRotation);
        actor2->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
        
         auto ico_actor3 = Actor::SpawnAttached(*actor);
         auto ico_meshComp3= MeshComponent::Create(*(ico_actor3.get()));
         auto ico_meshPtr3 =  ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(1, nullptr, "Textures/Tree.png"));
         ico_meshComp3->SetMesh(ico_meshPtr3);
         ico_actor3->SetPosition(Vector3(-1.0f, 0.0f ,  2.0f));
         ico_actor3->SetScale(0.5f);
        

    }
    
    
    return actor;
}


ActorPtr Tree::buildEverGreen(int lvl, Vector3 pos, Quaternion deltaRotation) {
    
	auto actor = Actor::Spawn(Game::Get());
    auto meshComp = MeshComponent::Create(*(actor.get()));
    auto meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(1));
    meshComp->SetMesh(meshPtr);
    actor->SetPosition(Vector3(pos.x, pos.y, pos.z));
	actor->SetScale(3.0f);
    actor->SetRotation(deltaRotation);

	auto actor2 = Actor::SpawnAttached(*actor);
    auto meshComp2 = MeshComponent::Create(*(actor2.get()));
    auto meshPtr2 =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(2));
    meshComp2->SetMesh(meshPtr2);
	actor2->SetPosition(Vector3(0.0f, 0.0f, 1.0f));

	return actor;
}

ActorPtr Tree::buildFluffyTree(int lvl, Vector3 pos, Quaternion deltaRotation) {
    
    //Branch
    auto actor = Actor::Spawn(Game::Get());
    auto meshComp = MeshComponent::Create(*(actor.get()));
    auto meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(1));
    meshComp->SetMesh(meshPtr);
    actor->SetPosition(Vector3(pos.x, pos.y, pos.z));
    actor->SetScale(20.0f);
    actor->SetRotation(deltaRotation);

    
    std::vector<ActorPtr> mProceduralActors;
    
    for (int i = 0; i < lvl; ++i)
    {
        auto actor2 = Actor::SpawnAttached(*actor);
        auto meshComp2 = MeshComponent::Create(*(actor2.get()));
        auto procMesh2 = ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(1, nullptr, "Textures/Tree.png"));
        meshComp2->SetMesh(procMesh2);
        actor2->SetScale(20.f - i * 5.0f);
        mProceduralActors.push_back(actor2);
    }
    
    for (int i = 0; i < lvl; ++i)
    {
        mProceduralActors[i]->SetPosition(Vector3(pos.x, pos.y, pos.z + 40.0f + 20.0f * i));
    }

    return actor;
}

ActorPtr Tree::buildGrass(Vector3 pos, Quaternion deltaRotation) {
    auto actor = Actor::Spawn(Game::Get());
    auto meshComp = MeshComponent::Create(*(actor.get()));
    auto meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(3));
    meshComp->SetMesh(meshPtr);
    actor->SetPosition(Vector3(pos.x, pos.y, pos.z));
    actor->SetRotation(deltaRotation);
    actor->SetScale(0.4f);
    return actor;
}







