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
#include "Tree.h"

class Planet : public Actor
{
	DECL_ACTOR(Planet, Actor);
    
    MeshComponentPtr mMesh;
	size_t mCurrentIterations;
    TreePtr mTree;

	MeshComponentPtr mWaterMesh;

	int mPerlinSeed;

	void Deform(std::vector<Vertex>& verts);
    
public:
    
	Planet(class Game& game);

	void SetIcoIterations(size_t iterations, int perlinSeed);
    void addFoliage();

};

DECL_PTR(Planet);
