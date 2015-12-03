//
//  GameMode.h
//  Game-mac
//
//  Created by Matthew Pohlmann on 8/8/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "AudioComponent.h"
#include "HUD.h"
#include "Ship.h"
#include "Planet.h"
#include "GameTimers.h"
#include "Tree.h"

class GameMode : public Actor
{
    DECL_ACTOR(GameMode, Actor);
public:
    GameMode(Game& game);
    
    virtual void BeginPlay() override;

private:

	std::vector<PlanetPtr> mPlanets;
	void RegenerateWorld(int icoIterations);
    
    AudioComponentPtr mAudio;
    HUDPtr mHud;
	ShipPtr mShip;
    TreePtr mTree;

	void RegenerateLevel0() { RegenerateWorld(0); }
	void RegenerateLevel1() { RegenerateWorld(1); }
	void RegenerateLevel2() { RegenerateWorld(2); }
	void RegenerateLevel3() { RegenerateWorld(3); }
	void RegenerateLevel4() { RegenerateWorld(4); }
	void RegenerateLevel5() { RegenerateWorld(5); }
	void RegenerateLevel6() { RegenerateWorld(6); }
	void RegenerateLevel7() { RegenerateWorld(7); }

};

DECL_PTR(GameMode);
