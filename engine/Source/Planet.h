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

public:
    
	Planet(class Game& game);
	virtual ~Planet();

	void SetIcoIterations(size_t iterations, int perlinSeed);

protected:

	MeshComponentPtr mMesh;

	size_t mCurrentIterations;
	int mPerlinSeed;

	virtual void Generate() { }

	virtual void Cleanup() { }

};

DECL_PTR(Planet);
