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
#include "Random.h"

IMPL_ACTOR(Planet, Actor);

Planet::Planet(Game& game) : Super(game)
{
	mCurrentIterations = -1;
    mMesh = MeshComponent::Create(*this);
	SetIcoIterations(mCurrentIterations);
	SetScale(30.f);
}

void Deform(std::vector<Vertex>& verts)
{
    // deform based on perlin noise
    static const float MaxDeformation = 0.2f;
    PerlinNoise pnoise;
    for (auto& v : verts)
    {
        // [0, 1]
        double noise = pnoise.NoiseSample(v.mPos.x, v.mPos.y, v.mPos.z, 8, false);
        
        // [-1, 1]
        noise = (noise - 0.5f) * 2.0f;
        auto vv = noise * v.mNormal * MaxDeformation;
        v.mPos += vv;
        auto vv_mag = vv.Length();
        v.mTexCoord.x = fmin(vv_mag*3, 1.0f);
        v.mTexCoord.y = (1.0f - fmin(vv_mag*3, 1.0f));
    }
}

void Planet::SetIcoIterations(size_t iterations)
{
	if (iterations == mCurrentIterations) return;

	mCurrentIterations = iterations;

	// Create a new mesh with the new iteration count
    auto meshPtr = ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(iterations, Deform, "Textures/EarthGradient.png"));
	mMesh->SetMesh(meshPtr);

	// Get the shader we want for planets
	auto shader = Game::Get().GetAssetCache().Load<Shader>("Shaders/BasicMesh");
	if (shader)
	{
		// Create an instance of the shader for this planet so changes to planets don't affect other
		// actors using this shader.
		auto shaderInstance = shader->CreateShaderInstance();

		// Set up material defaults for planets
		shaderInstance->BindEmissiveColor(Vector3(0.1f, 0.1f, 0.5f));
		// etc...

		// Set new shader instance
		meshPtr->SetShader(shaderInstance);
	}
}

