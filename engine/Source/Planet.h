//
//  Planet.h
//  Game-mac
//
//  Created by Matthew Pohlmann on 11/29/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "Actor.h"
#include "MeshComponent.h"

class Planet : public Actor
{
	DECL_ACTOR(Planet, Actor);
    
    MeshComponentPtr mMesh;
	size_t mCurrentIterations;
    
public:
    
	Planet(class Game& game);

	void SetIcoIterations(size_t iterations);
    
};

DECL_PTR(Planet);
