//
//  HUD.h
//  Game-mac
//
//  Created by Matthew Pohlmann on 8/9/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "FontComponent.h"

class HUD : public Actor
{
    DECL_ACTOR(HUD, Actor);
public:
    HUD(Game& game);
    
    virtual void BeginPlay() override;
    
    void SetScore(int score);
    void SetTime(int time);
    void SetStatusText(const std::string& text, float duration = -1.0f);
    
private:
    FontComponentPtr mTextScore;
    FontComponentPtr mTextTime;
    FontComponentPtr mTextStatus;
    
    void ClearStatusText();
};

DECL_PTR(HUD);
