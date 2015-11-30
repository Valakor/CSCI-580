//
//  MeshComponent.cpp
//  Game-mac
//
//  Created by Matthew Pohlmann on 8/2/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "MeshComponent.h"
#include "Actor.h"
#include "Renderer.h"

IMPL_COMPONENT(MeshComponent, DrawComponent);

MeshComponent::MeshComponent(Actor& owner) : Super(owner)
{
    
}

void MeshComponent::Draw(class Renderer& render)
{
    if (mMesh && mMesh->GetShader())
    {
        render.DrawBasicMesh(mMesh->GetShader(), mMesh->GetVertexArray(), mMesh->GetTexture(0), mOwner.GetWorldTransform());
    }
}
