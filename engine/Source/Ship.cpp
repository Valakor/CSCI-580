//
//  Ship.cpp
//  Game-mac
//
//  Created by Matthew Pohlmann on 8/2/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "Ship.h"
#include "Game.h"
#include "Sound.h"
#include "Asteroid.h"
#include "SphereCollision.h"
#include "Mesh.h"
#include "CameraComponent.h"
#include "Checkpoint.h"
#include "IcoGenerator.h"

IMPL_ACTOR(Ship, Actor);

Ship::Ship(Game& game) : Super(game)
{
    mMesh = MeshComponent::Create(*this);
   // auto meshPtr = mGame.GetAssetCache().Load<Mesh>("Meshes/PlayerShip.itpmesh2");
   //  auto meshPtr =  ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(4));
    //mMesh->SetMesh(meshPtr);
    
    mInput = InputComponent::Create(*this, InputComponent::PreTick);
    mInput->SetLinearSpeed(400.0f);
    mInput->SetAngularSpeed(Math::Pi);
    
    auto collider = SphereCollision::Create(*this);
 //   collider->RadiusFromMesh(meshPtr);
    collider->SetScale(1.0f);
    
    mAudio = AudioComponent::Create(*this);

    auto engineSound = game.GetAssetCache().Load<Sound>("Sounds/ShipEngine.wav");
    mEngineSoundCue = mAudio->PlaySound(engineSound, true);
    mEngineSoundCue.Pause();

	mCamera = CameraComponent::Create( *this );
	mCamera->SetMinHorizontalFollowDistance( 200.0f );
	mCamera->SetMaxHorizontalFollowDistance( 250.0f );
	mCamera->SetVerticalFollowDistance( 100.f );
	mCamera->SetTargetOffset( 150.f );
	mCamera->SetSpringConstant( 200.0f );
	mCamera->SnapToIdealPosition();

	mGame.GetInput().BindAction( "Recenter", IE_Pressed, this, &Ship::Recenter );
}

void Ship::BeginPlay()
{
    Super::BeginPlay();
    
    mInput->BindYawAxis("Yaw");
	mInput->BindPitchAxis("Pitch");
    mInput->BindLinearAxis("Move");
}

void Ship::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
    
    if (Math::IsZero(mInput->GetLinearAxis()))
    {
        mEngineSoundCue.Pause();
    }
    else
    {
        mEngineSoundCue.Resume();
    }
}

void Ship::Recenter()
{
	SetRotation( Quaternion::Identity );
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	mCamera->SnapToIdealPosition();
}
