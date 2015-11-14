//
//  ProceduralMeshComponent.h
//  Game-windows
//
//  Created by Matthew Pohlmann on 11/14/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "MeshComponent.h"
#include "Mesh.h"

class ProceduralMeshComponent : public MeshComponent
{
	DECL_COMPONENT(ProceduralMeshComponent, MeshComponent);
    
public:
    
	ProceduralMeshComponent(Actor& owner);

    virtual void Draw(class Renderer& render) override;
	void Generate();

protected:

	virtual void GenerateMesh(std::vector<Vertex>& verts, std::vector<GLuint>& indices);
    
};

DECL_PTR(ProceduralMeshComponent);
