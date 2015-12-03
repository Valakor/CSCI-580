//
//  Tree.h
//  Game-mac
//
//  Created by Shazzy Gustafson on 11/19/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "Actor.h"
#include "InputComponent.h"
#include "Texture.h"
#include "MeshComponent.h"


class Tree: public Actor
{
    DECL_ACTOR(Tree, Actor);
    
 //   InputComponentPtr mInput;
    
 //   MeshComponentPtr mMesh;

    
public:
    
    Tree(class Game& game);
    static ActorPtr buildTree(int lvl, Vector3 pos, Quaternion rot);
    static ActorPtr buildEverGreen(int lvl, Vector3 pos, Quaternion rot);
    static ActorPtr buildFluffyTree(int lvl, Vector3 pos, Quaternion rot);
    static ActorPtr buildGrass(Vector3 pos, Quaternion rot);
    
};

DECL_PTR(Tree);