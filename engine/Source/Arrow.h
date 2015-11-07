//
//  Arrow.h
//  Game-windows
//
//  Created by Matthew Pohlmann on 11/6/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "Actor.h"

class Arrow : public Actor
{
	DECL_ACTOR( Arrow, Actor );
    
public:
    
	Arrow( class Game& game );
	virtual void BeginPlay() override;
	virtual void Tick( float deltaTime ) override;

	void SetPlayer( ActorPtr player ) { mPlayer = player; }
	void SetTarget( const Vector3& target ) { mTarget = target; }

private:

	void UpdateWorldPosition();
	void UpdateRotation();

	ActorPtr mPlayer;
	Vector3 mTarget;
    
};

DECL_PTR( Arrow );
