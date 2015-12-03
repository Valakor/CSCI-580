//
//  PlanetRinged.cpp
//  Game-windows
//
//  Created by Matthew Pohlmann on 12/03/15.
//

#include "PlanetRinged.h"
#include "Game.h"
#include "ProceduralMesh.h"
#include "IcoGenerator.h"
#include "Rock.h"
#include "Random.h"

IMPL_ACTOR(PlanetRinged, Planet);

PlanetRinged::PlanetRinged(Game& game) : Super(game)
{

}

void PlanetRinged::Tick(float deltaTime)
{
	Vector3 up = GetWorldTransform().GetZAxis();
	float rate = 0.06f * deltaTime;
	Quaternion deltaRot(up, rate);
	Quaternion newRot = Concatenate(GetRotation(), deltaRot);
	SetRotation(newRot);
}

void PlanetRinged::Cleanup()
{
	for (auto tree : mRocks)
	{
		tree->SetIsAlive(false);
	}
	mRocks.clear();
	mChildren.clear();
}

void PlanetRinged::Generate()
{
	// Create the planet geometry mesh
	auto meshPtr = ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(mCurrentIterations));
	mMesh->SetMesh(meshPtr);

	// Get the shader we want for planets
	auto shader = Game::Get().GetAssetCache().Load<Shader>("Shaders/BasicMesh");
	if (shader)
	{
		// Create an instance of the shader for this planet so changes to planets don't affect other
		// actors using this shader.
		auto shaderInstance = shader->CreateShaderInstance();

		// Set up material defaults for planets
		shaderInstance->BindDiffuseColor(Vector3(0.2f, 0.2f, 0.2f));
		shaderInstance->BindSpecularColor(Vector3(0.5f, 0.5f, 0.5f));
		shaderInstance->BindSpecPower(4.0f);
		// etc...

		// Set new shader instance
		meshPtr->SetShader(shaderInstance);
	}

	GenerateRing();
}

void PlanetRinged::GenerateRing()
{
	// Spawn Asteroids
	const int NUM_ROCKS = 200;
	for (int i = 0; i < NUM_ROCKS; ++i)
	{
		auto Rock = Rock::SpawnAttached(*this);
		float s = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) + 0.5f;
		Rock->SetScale(s * 0.075f);
		Rock->SetRotation(Random::GetRotation());

		static const float HI = 0.12f;
		static const float LO = -HI;

		int a, b, c;
		float z;

		while (true)
		{
			a = rand() % 31 - 15;
			b = rand() % 31 - 15;
			c = a * a + b * b;
			z = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));

			if (c >= 144 && c <= 225) break;
		}
		Rock->SetPosition(Vector3(a / 9.8f, b / 9.8f, z));
		mRocks.push_back(Rock);
	}
}
