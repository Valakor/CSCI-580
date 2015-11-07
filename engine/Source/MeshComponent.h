//
//  MeshComponent.h
//  Game-mac
//
//  Created by Matthew Pohlmann on 8/2/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "DrawComponent.h"
#include "Mesh.h"

class MeshComponent : public DrawComponent
{
    DECL_COMPONENT(MeshComponent, DrawComponent);
    
    MeshPtr mMesh;
    
public:
    
    MeshComponent(Actor& owner);
    
    virtual void Draw(class Renderer& render) override;
    
    void SetMesh(MeshPtr mesh) { mMesh = mesh; }
    MeshPtr GetMesh() const { return mMesh; }
    
};

DECL_PTR(MeshComponent);
