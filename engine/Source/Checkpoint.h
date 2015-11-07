//
//  Checkpoint.h
//  Game-windows
//
//  Created by Matthew Pohlmann on 11/5/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "Actor.h"

class Checkpoint : public Actor
{
    DECL_ACTOR(Checkpoint, Actor);
    
public:
    
	Checkpoint( class Game& game );
    
};

DECL_PTR( Checkpoint );
