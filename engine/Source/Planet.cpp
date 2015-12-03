//
//  Planet.cpp
//  Game-mac
//
//  Created by Matthew Pohlmann on 11/29/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "Planet.h"
#include "Game.h"
#include "ProceduralMesh.h"
#include "IcoGenerator.h"
#include "Shader.h"
#include "PerlinNoise.h"
#include <functional>

IMPL_ACTOR(Planet, Actor);

std::vector<Vector3> gColor = {
	Vector3(0.9f, 0.9f, 0.7f), // Beach
	Vector3(0.0f, 1.0f, 0.0f), // Grass
	Vector3(0.4f, 0.4f, 0.3f), // Rocks
	Vector3(0.4f, 0.4f, 0.3f), // Rocks
	Vector3(0.4f, 0.4f, 0.3f), // Rocks
	Vector3(1.0f, 1.0f, 1.0f), // Snow
	Vector3(1.0f, 1.0f, 1.0f), // Snow
	Vector3(1.0f, 1.0f, 1.0f), // Snow
	Vector3(1.0f, 1.0f, 1.0f), // Snow
	Vector3(1.0f, 1.0f, 1.0f), // Snow
	Vector3(1.0f, 1.0f, 1.0f), // Snow
	Vector3(1.0f, 1.0f, 1.0f), // Snow
	Vector3(1.0f, 1.0f, 1.0f), // Snow
	Vector3(1.0f, 1.0f, 1.0f), // Snow
	Vector3(1.0f, 1.0f, 1.0f), // Snow
	Vector3(1.0f, 1.0f, 1.0f)  // Snow
};

Planet::Planet(Game& game) : Super(game)
{
	mCurrentIterations = -1;
    mMesh = MeshComponent::Create(*this);
	mWaterMesh = MeshComponent::Create(*this);
	SetIcoIterations(mCurrentIterations, -1);
	SetScale(200.f);
}

Planet::~Planet()
{
	CleanupFoliage();
}

void Planet::Deform(std::vector<Vertex>& verts)
{
    // deform based on perlin noise
    static const float MaxDeformation = 0.5f;
    PerlinNoise pnoise(mPerlinSeed);
    for (auto& v : verts)
    {
        // [0, 1]
        float noise = static_cast<float>(pnoise.NoiseSample(v.mPos.x, v.mPos.y, v.mPos.z, 8, false) - 0.01);

		// Vertex position deformation
		auto vv = noise * v.mNormal * MaxDeformation;
		v.mPos += vv;

		// Store altitude in U of UV coordinate
		v.mTexCoord.x = noise + 0.01f;

		// Get color interp fraction and set vertex color
		float colorFrac = noise * (gColor.size() - 1);
		int lowerIndex = static_cast<int>(colorFrac);
		colorFrac -= lowerIndex;
		Vector3 finalColor = (1.0f - colorFrac) * gColor[lowerIndex] + colorFrac * gColor[lowerIndex + 1];
		v.mColor = finalColor;
    }

	addFoliage(verts);
}

void Planet::CleanupFoliage()
{
	for (auto tree : mTrees)
	{
		tree->SetIsAlive(false);
	}
	mTrees.clear();
}

void Planet::SetIcoIterations(size_t iterations, int perlinSeed)
{
	if (iterations == mCurrentIterations) return;

	mCurrentIterations = iterations;
	mPerlinSeed = perlinSeed;

	CleanupFoliage();

	// Create the ocean / water level mesh
	auto meshPtr = ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(iterations));
	mWaterMesh->SetMesh(meshPtr);

	// Get the shader we want for water on planets
	auto shader = Game::Get().GetAssetCache().Load<Shader>("Shaders/BasicMesh");
	if (shader)
	{
		// Create an instance of the shader for this planet so changes to planets don't affect other
		// actors using this shader.
		auto shaderInstance = shader->CreateShaderInstance();

		// Set up material defaults for planets
	    shaderInstance->BindDiffuseColor(Vector3(0.27f, 0.6f, 0.94f));
		shaderInstance->BindSpecPower(8.0f);
		// etc...

		// Set new shader instance
		meshPtr->SetShader(shaderInstance);
	}

	// Create the planet geometry mesh
	DeformationFunction func = std::bind(&Planet::Deform, this, std::placeholders::_1);
	meshPtr = ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(iterations, func));
	mMesh->SetMesh(meshPtr);

	// Get the shader we want for planets
	if (shader)
	{
		// Create an instance of the shader for this planet so changes to planets don't affect other
		// actors using this shader.
		auto shaderInstance = shader->CreateShaderInstance();

		// Set up material defaults for planets
		shaderInstance->BindSpecPower(4.0f);
		// etc...

		// Set new shader instance
		meshPtr->SetShader(shaderInstance);
	}
    
}



void Planet::addFoliage(const std::vector<Vertex>& verts) {
    for(int i = 0; i < verts.size(); i++) {
        Vector3 pos =  verts[i].mPos * GetScale() + GetPosition();
        
		Vector3 normal = verts[i].mNormal;
		static const Vector3 up = Vector3::UnitZ;

		float dot = Dot(normal, up);
		Quaternion deltaRotation;

		if (Math::Abs(dot) > 0.9995f)
		{
			deltaRotation = Quaternion::Identity;
		}
		else
		{
			float deltaAngle = Math::Acos(dot);

			Vector3 axis = Cross(up, normal);
			axis.Normalize();

			deltaRotation = Quaternion( axis,  deltaAngle );
		}

		float altitude = verts[i].mTexCoord.x;
		if (altitude > 0.0f)
		{
			mTrees.push_back(Tree::buildEverGreen(2,pos, deltaRotation));
		}

    }
    
}

