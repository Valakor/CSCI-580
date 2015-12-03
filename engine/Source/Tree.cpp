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
    
    
 /*   auto ico_actor = Actor::Spawn(mGame);
    auto ico_meshComp = MeshComponent::Create(*(ico_actor.get()));
    auto ico_meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(1, nullptr, "Textures/Tree.png"));
    ico_meshComp->SetMesh(ico_meshPtr);
    ico_actor->SetPosition(Vector3(pos.x, pos.y, pos.z + 80.0f));
    ico_actor->SetScale(30.0f); */
    
    
    
    if(lvl > 1) {
        auto actor2 = Actor::Spawn(mGame);
        auto meshComp2 = MeshComponent::Create(*(actor2.get()));
        auto meshPtr2 =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(1));
        meshComp2->SetMesh(meshPtr2);
        actor2->SetScale(17.0f);
        float deltaAngle = .7f;
        Vector3 rotationAxis = Vector3(0,1,0);
        Quaternion deltaRotation = Quaternion( rotationAxis, deltaAngle );
        actor2->SetRotation(deltaRotation);
        actor2->SetPosition(Vector3(pos.x, pos.y , pos.z + 30.0f));
        
        
  /*      auto ico_actor = Actor::Spawn(mGame);
        auto ico_meshComp = MeshComponent::Create(*(ico_actor.get()));
        auto ico_meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(1, nullptr, "Textures/Tree.png"));
        ico_meshComp->SetMesh(ico_meshPtr);
        ico_actor->SetPosition(Vector3(pos.x + 30.0f, pos.y , pos.z + 60.0f));
        ico_actor->SetScale(20.0f); */
    }
    
    if (lvl > 2) {
        auto actor2 = Actor::Spawn(mGame);
        auto meshComp2 = MeshComponent::Create(*(actor2.get()));
        auto meshPtr2 =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(1));
        meshComp2->SetMesh(meshPtr2);
        actor2->SetScale(17.0f);
        float deltaAngle = -0.7f;
        Vector3 rotationAxis = Vector3(0,1,0);
        Quaternion deltaRotation = Quaternion( rotationAxis, deltaAngle );
        actor2->SetRotation(deltaRotation);
        actor2->SetPosition(Vector3(pos.x, pos.y , pos.z + 30.0f));
        
     /*    auto ico_actor = Actor::Spawn(mGame);
         auto ico_meshComp = MeshComponent::Create(*(ico_actor.get()));
         auto ico_meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(1, nullptr, "Textures/Tree.png"));
         ico_meshComp->SetMesh(ico_meshPtr);
         ico_actor->SetPosition(Vector3(pos.x - 30.0f, pos.y , pos.z + 60.0f));
         ico_actor->SetScale(20.0f); */
        
        auto actor3 = Actor::Spawn(mGame);
        auto meshComp3 = MeshComponent::Create(*(actor3.get()));
        auto meshPtr3 =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(1));
        meshComp3->SetMesh(meshPtr3);
        actor3->SetScale(8.0f);
        float deltaAngle3 = -0.34f;
        Vector3 rotationAxis3 = Vector3(0,1,0);
        Quaternion deltaRotation3 = Quaternion( rotationAxis3, deltaAngle3 );
        actor3->SetRotation(deltaRotation3);
        actor3->SetPosition(Vector3(pos.x + 17.0f, pos.y , pos.z + 52.0f));
        
        auto actor4 = Actor::Spawn(mGame);
        auto meshComp4 = MeshComponent::Create(*(actor4.get()));
        auto meshPtr4 =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(1));
        meshComp4->SetMesh(meshPtr4);
        actor4->SetScale(8.0f);
        float deltaAngle4 = -4.74f;
        Vector3 rotationAxis4 = Vector3(0,1,0);
        Quaternion deltaRotation4 = Quaternion( rotationAxis4, deltaAngle4 );
        actor4->SetRotation(deltaRotation4);
        actor4->SetPosition(Vector3(pos.x + 18.0f, pos.y , pos.z + 50.0f));
        
        //////
        
        auto actor5 = Actor::Spawn(mGame);
        auto meshComp5 = MeshComponent::Create(*(actor5.get()));
        auto meshPtr5 =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(1));
        meshComp5->SetMesh(meshPtr5);
        actor5->SetScale(8.0f);
        float deltaAngle5 = -1.50f;
        Vector3 rotationAxis5 = Vector3(0,1,0);
        Quaternion deltaRotation5 = Quaternion( rotationAxis5, deltaAngle5 );
        actor5->SetRotation(deltaRotation5);
        actor5->SetPosition(Vector3(pos.x - 18.0f, pos.y , pos.z + 50.0f));
        
        auto actor6 = Actor::Spawn(mGame);
        auto meshComp6 = MeshComponent::Create(*(actor6.get()));
        auto meshPtr6 =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(1));
        meshComp6->SetMesh(meshPtr6);
        actor6->SetScale(8.0f);
        float deltaAngle6 = 0.34f;
        Vector3 rotationAxis6 = Vector3(0,1,0);
        Quaternion deltaRotation6 = Quaternion( rotationAxis6, deltaAngle6 );
        actor6->SetRotation(deltaRotation6);
        actor6->SetPosition(Vector3(pos.x - 17.0f, pos.y , pos.z + 52.0f));
    }
    
    
    
}


void Tree::buildEverGreen(int lvl, Vector3 pos, Quaternion deltaRotation) {
    
    auto actor = Actor::Spawn(mGame);
    auto meshComp = MeshComponent::Create(*(actor.get()));
    auto meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(1));
    meshComp->SetMesh(meshPtr);
    actor->SetPosition(Vector3(pos.x, pos.y, pos.z));
    actor->SetScale(10.0f);
    actor->SetRotation(deltaRotation);
    
    
    auto actor2 = Actor::Spawn(mGame);
    auto meshComp2 = MeshComponent::Create(*(actor2.get()));
    auto meshPtr2 =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(2));
    meshComp2->SetMesh(meshPtr2);
    actor2->SetPosition(Vector3(pos.x, pos.y, pos.z + 10.0f));
    actor2->SetScale(5.0f);
    actor2->SetRotation(deltaRotation);
}

void Tree::buildFluffyTree(int lvl, Vector3 pos) {
    
    //Branch
    auto actor = Actor::Spawn(mGame);
    auto meshComp = MeshComponent::Create(*(actor.get()));
    auto meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(1));
    meshComp->SetMesh(meshPtr);
    actor->SetPosition(Vector3(pos.x, pos.y, pos.z));
    actor->SetScale(20.0f);

    
    std::vector<ActorPtr> mProceduralActors;
    
    for (int i = 0; i < lvl; ++i)
    {
        auto actor = Actor::Spawn(mGame);
        auto meshComp = MeshComponent::Create(*(actor.get()));
        auto procMesh = ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(1, nullptr, "Textures/Tree.png"));
        meshComp->SetMesh(procMesh);
        actor->SetScale(20.f - i * 5.0f);
        mProceduralActors.push_back(actor);
    }
    
    for (int i = 0; i < lvl; ++i)
    {
        mProceduralActors[i]->SetPosition(Vector3(pos.x, pos.y, pos.z + 40.0f + 20.0f * i));
    }

    
}

void Tree::buildGrass(Vector3 pos) {
    auto actor = Actor::Spawn(mGame);
    auto meshComp = MeshComponent::Create(*(actor.get()));
    auto meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<Foliage>(3));
    meshComp->SetMesh(meshPtr);
    actor->SetPosition(Vector3(pos.x, pos.y, pos.z));
}







