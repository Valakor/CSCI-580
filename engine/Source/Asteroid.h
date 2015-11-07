//
//  Asteroid.h
//  Game-mac
//
//  Created by Matthew Pohlmann on 8/1/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "Actor.h"

class Asteroid : public Actor
{
    DECL_ACTOR(Asteroid, Actor);
    
public:
    
    Asteroid(class Game& game);
    
};

DECL_PTR(Asteroid);
