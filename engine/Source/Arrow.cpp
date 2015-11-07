//
//  Arrow.cpp
//  Game-windows
//
//  Created by Matthew Pohlmann on 11/6/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "Arrow.h"
#include "Game.h"
#include "MeshComponent.h"
#include "Renderer.h"

IMPL_ACTOR( Arrow, Actor );

Arrow::Arrow( Game& game ) : Super( game )
	, mPlayer( nullptr )
	, mTarget( Vector3::Zero )
{
    auto mesh = MeshComponent::Create(*this);
    auto meshPtr = game.GetAssetCache().Load<Mesh>("Meshes/Arrow.itpmesh2");
    mesh->SetMesh(meshPtr);
}

void Arrow::BeginPlay()
{
	Super::BeginPlay();
	UpdateWorldPosition();
}

void Arrow::Tick( float deltaTime )
{
	Super::Tick( deltaTime );
	UpdateWorldPosition();
	UpdateRotation();
}

void Arrow::UpdateWorldPosition()
{
	Vector3 worldPosition = mGame.GetRenderer().Unproject( Vector3( 0.0f, 150.0f, 0.6f ) );
	SetPosition( worldPosition );
}

void Arrow::UpdateRotation()
{
	Vector3 lookDirection = Normalize( mTarget - mPlayer->GetPosition() );
	float dot = Dot( Vector3::UnitX, lookDirection );

	if ( Math::Abs( dot ) > 0.9995f )
	{
		SetRotation( Quaternion::Identity );
		return;
	}

	float angle = Math::Acos( dot );
	Vector3 axis = Normalize( Cross( Vector3::UnitX, lookDirection ) );

	SetRotation( Quaternion( axis, angle ) );
}

