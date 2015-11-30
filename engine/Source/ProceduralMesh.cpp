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
	// Simple diamond-shaped thing for testing purposes
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
	if (!mGenerator)
	{
		return false;
	}

	std::vector<Vertex> verts;
	std::vector<GLuint> indices;

	mGenerator->GenerateMesh(verts, indices, mTextures, mRadius);

	// Load default texture if none given by generator
	if (mTextures.size() == 0)
	{
		auto mTexture = Game::Get().GetAssetCache().Load<Texture>("Textures/Default.png");
		if (!mTexture)
		{
			SDL_Log("Failed to load default texture");
			return false;
		}
		else
		{
			mTextures.push_back(mTexture);
		}
	}

	// Load default shader if none given by generator
	if (!mShader)
	{
		mShader = Game::Get().GetAssetCache().Load<Shader>("Shaders/BasicMesh");
		if (!mShader)
		{
			SDL_Log("Failed to load default basic mesh shader");
			return false;
		}
	}

	mVertexArray = VertexArray::Create(verts.data(), verts.size(), indices.data(), indices.size());

	return true;
}

