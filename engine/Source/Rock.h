//
//  Rock.h
//  Game-mac
//
//  Created by Shazzy Gustafson on 11/29/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "Actor.h"

class Rock: public Actor
{
    DECL_ACTOR(Rock, Actor);
    
public:
    
    Rock(class Game& game);
    
};

DECL_PTR(Rock);
