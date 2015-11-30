//
//  Sky.h
//  Game-mac
//
//  Created by Shazzy Gustafson on 11/29/15.
//  Copyright © 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "Actor.h"

class Sky : public Actor
{
    DECL_ACTOR(Sky, Actor);
    
public:
    
    Sky(class Game& game);
    
};

DECL_PTR(Sky);
