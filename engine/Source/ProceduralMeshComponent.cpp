//
//  ProceduralMeshComponent.cpp
//  Game-windows
//
//  Created by Matthew Pohlmann on 11/14/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "ProceduralMeshComponent.h"
#include "Actor.h"
#include "Renderer.h"

IMPL_COMPONENT(ProceduralMeshComponent, MeshComponent);

ProceduralMeshComponent::ProceduralMeshComponent(Actor& owner) : Super(owner)
{
    
}

void ProceduralMeshComponent::Draw(class Renderer& render)
{
	MeshPtr mesh = GetMesh();
    if (mesh)
    {
		render.DrawBasicMesh(mesh->GetVertexArray(), mesh->GetTexture(0), mOwner.GetWorldTransform());
    }
}

void ProceduralMeshComponent::Generate()
{
	std::vector<Vertex> verts;
	std::vector<GLuint> indices;

	GenerateMesh(verts, indices);

	VertexArrayPtr vertexArray = VertexArray::Create(verts.data(), verts.size(), indices.data(), indices.size());
	MeshPtr newMesh = std::make_shared<Mesh>(vertexArray, std::vector<TexturePtr>(), 1.0f);
	SetMesh(newMesh);
}

void ProceduralMeshComponent::GenerateMesh(std::vector<Vertex>& verts, std::vector<GLuint>& indices)
{
	verts.emplace_back(Vector3(1.f, 0.f, 0.f), Vector3(1.f, 0.f, 0.f), Vector2(0.f, 0.f));
	verts.emplace_back(Vector3(-1.f, 0.f, 0.f), Vector3(-1.f, 0.f, 0.f), Vector2(0.f, 0.f));
	verts.emplace_back(Vector3(0.f, 1.f, 0.f), Vector3(0.f, 1.f, 0.f), Vector2(0.f, 0.f));
	verts.emplace_back(Vector3(0.f, -1.f, 0.f), Vector3(0.f, -1.f, 0.f), Vector2(0.f, 0.f));
	
	verts.emplace_back(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 1.f), Vector2(0.f, 0.f));
	verts.emplace_back(Vector3(0.f, 0.f, -1.f), Vector3(0.f, 0.f, -1.f), Vector2(0.f, 0.f));

	indices.push_back(0);
	indices.push_back(4);
	indices.push_back(3);

	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(1);
	
	indices.push_back(1);
	indices.push_back(4);
	indices.push_back(2);

	indices.push_back(2);
	indices.push_back(4);
	indices.push_back(0);

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(5);

	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(5);

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(5);

	indices.push_back(2);
	indices.push_back(5);
	indices.push_back(0);
}
