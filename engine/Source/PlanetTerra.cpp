//
//  PlanetTerra.cpp
//  Game-windows
//
//  Created by Matthew Pohlmann on 12/03/15.
//

#include "PlanetTerra.h"
#include "Game.h"
#include "ProceduralMesh.h"
#include "PerlinNoise.h"
#include "IcoGenerator.h"
#include <functional>

IMPL_ACTOR(PlanetTerra, Planet);

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

PlanetTerra::PlanetTerra(Game& game) : Super(game)
{
	mCurrentIterations = -1;
	mMesh = MeshComponent::Create(*this);
	mWaterMesh = MeshComponent::Create(*this);
	SetIcoIterations(mCurrentIterations, -1);
	SetScale(200.f);
}

void PlanetTerra::Tick(float deltaTime)
{
	Vector3 up = GetWorldTransform().GetZAxis();
	float rate = 0.03f * deltaTime;
	Quaternion deltaRot(up, rate);
	Quaternion newRot = Concatenate(GetRotation(), deltaRot);
	SetRotation(newRot);
}

void PlanetTerra::Deform(std::vector<Vertex>& verts)
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

	AddFoliage(verts);
}

void PlanetTerra::Cleanup()
{
	for (auto tree : mFoliage)
	{
		tree->SetIsAlive(false);
	}
	mFoliage.clear();
	mChildren.clear();
}

void PlanetTerra::Generate()
{
	// Create the ocean / water level mesh
	auto meshPtr = ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(mCurrentIterations));
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
		shaderInstance->BindSpecPower(10.0f);
		// etc...

		// Set new shader instance
		meshPtr->SetShader(shaderInstance);
	}

	// Create the planet geometry mesh
	DeformationFunction func = std::bind(&PlanetTerra::Deform, this, std::placeholders::_1);
	meshPtr = ProceduralMesh::StaticCreate(std::make_shared<IcoGenerator>(mCurrentIterations, func));
	mMesh->SetMesh(meshPtr);

	// Get the shader we want for planets
	if (shader)
	{
		// Create an instance of the shader for this planet so changes to planets don't affect other
		// actors using this shader.
		auto shaderInstance = shader->CreateShaderInstance();

		// Set up material defaults for planets
		shaderInstance->BindSpecularColor(Vector3(0.5f, 0.5f, 0.5f));
		shaderInstance->BindSpecPower(4.0f);
		// etc...

		// Set new shader instance
		meshPtr->SetShader(shaderInstance);
	}
}

void PlanetTerra::AddFoliage(const std::vector<Vertex>& verts)
{
	for (size_t i = 0; i < verts.size(); i++)
	{
		Vector3 pos = verts[i].mPos;

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

			deltaRotation = Quaternion(axis, deltaAngle);
		}

		float altitude = verts[i].mTexCoord.x;
		if (altitude > 0.0f)
		{
			if (altitude > 0.25f)
			{
				int add = rand() % 5;
				if (add == 0)
				{
					auto everGreen = Tree::buildEverGreen(2, pos, deltaRotation);
					mFoliage.push_back(everGreen);
					AddChild(everGreen);
				}
			}
			else if (altitude < 0.2f)
			{
				int add = rand() % 30;

				if (add == 0)
				{
					int lvl = rand() % 3 + 1;
					auto tree = Tree::buildTree(lvl, pos, deltaRotation);
					mFoliage.push_back(tree);
					AddChild(tree);
				}
				else if (add >= 0 && add <= 3)
				{
					auto grass = Tree::buildGrass(pos, deltaRotation);
					mFoliage.push_back(grass);
					AddChild(grass);
				}
			}
		}
	}
}