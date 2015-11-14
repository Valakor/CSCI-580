//
//  ProceduralMesh.cpp
//  Game-windows
//
//  Created by Matthew Pohlmann on 11/14/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "ProceduralMesh.h"
#include "Renderer.h"
#include "Game.h"


void MeshGenerator::GenerateMesh(std::vector<Vertex>& verts, std::vector<GLuint>& indices, std::vector<TexturePtr>& textures, float& radius)
{
	radius = 1.0f;

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

bool ProceduralMesh::Generate()
{
	std::vector<Vertex> verts;
	std::vector<GLuint> indices;

	mGenerator.GenerateMesh(verts, indices, mTextures, mRadius);

	if (mTextures.size() == 0)
	{
		mTextures.push_back(Game::Get().GetAssetCache().Load<Texture>("Textures/Default.png"));
	}

	mVertexArray = VertexArray::Create(verts.data(), verts.size(), indices.data(), indices.size());

	return true;
}

