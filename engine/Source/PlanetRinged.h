//
//  PlanetRinged.h
//  Game-windows
//
//  Created by Matthew Pohlmann on 12/03/15.
//

#pragma once

#include "Planet.h"

class PlanetRinged : public Planet
{
	DECL_ACTOR(PlanetRinged, Planet);

public:

	PlanetRinged(Game& game);
	virtual ~PlanetRinged() = default;

	virtual void Tick(float deltaTime) override;

protected:

	virtual void Generate() override;
	virtual void Cleanup() override;

private:

	std::vector<ActorPtr> mRocks;

	void GenerateRing();
};

DECL_PTR(PlanetRinged);
