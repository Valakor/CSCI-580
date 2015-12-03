//
//  PlanetTerra.h
//  Game-windows
//
//  Created by Matthew Pohlmann on 12/03/15.
//

#pragma once

#include "Planet.h"

class PlanetTerra : public Planet
{
	DECL_ACTOR(PlanetTerra, Planet);

public:

	PlanetTerra(Game& game);
	virtual ~PlanetTerra() = default;

	virtual void Tick(float deltaTime) override;

protected:

	virtual void Generate() override;
	virtual void Cleanup() override;

private:

	MeshComponentPtr mWaterMesh;
	std::vector<ActorPtr> mFoliage;

	void Deform(std::vector<Vertex>& verts);
	void AddFoliage(const std::vector<Vertex>& verts);

};

DECL_PTR(PlanetTerra);
