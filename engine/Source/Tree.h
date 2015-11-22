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
    void buildTree(int lvl, int base);
 //   virtual void BeginPlay() override;
 //   virtual void Tick(float deltaTime) override;
    
 //   void Recenter();
    
};

DECL_PTR(Tree);