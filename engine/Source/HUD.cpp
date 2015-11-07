//
//  HUD.cpp
//  Game-mac
//
//  Created by Matthew Pohlmann on 8/9/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "HUD.h"
#include "Game.h"
#include <sstream>

IMPL_ACTOR(HUD, Actor);

HUD::HUD(Game& game) : Super(game)
{
    
}

void HUD::BeginPlay()
{
    Super::BeginPlay();
    
    SetPosition(Vector3::Zero);
    int width = mGame.GetRenderer().GetWidth();
    int height = mGame.GetRenderer().GetHeight();
    
    auto font = mGame.GetAssetCache().Load<Font>("Fonts/Carlito-Regular.ttf");
    
    auto scoreActor = Actor::SpawnAttached(*this);
	scoreActor->SetPosition( Vector3( 0.0f, height / 2.0f - 30.0f, 0.0f ) );
	mTextScore = FontComponent::Create( *scoreActor );
	mTextScore->SetFont( font );
	mTextScore->SetText( "Score: 0", Color::White, 30 );
	mTextScore->SetAlignment( FontComponent::AlignCenter );
    
    auto timeActor = Actor::SpawnAttached(*this);
	timeActor->SetPosition( Vector3( 0.0f, height / 2.0f - 65.0f, 0.0f ) );
	mTextTime = FontComponent::Create( *timeActor );
	mTextTime->SetFont( font );
	mTextTime->SetText( "Time: 999", Color::Green, 30 );
	mTextTime->SetAlignment( FontComponent::AlignCenter );
    
    mTextStatus = FontComponent::Create(*this);
    mTextStatus->SetFont(font);
    mTextStatus->SetText("STATUS MESSAGE", Color::Red, 56);
    mTextStatus->SetAlignment(FontComponent::AlignCenter);
}

void HUD::SetScore( int score )
{
    std::stringstream ss;
    ss << "Score: " << score;
    
	mTextScore->SetText( ss.str(), Color::White, 30 );
}

void HUD::SetTime( int time )
{
    std::stringstream ss;
    ss << "Time: " << time;
    
	mTextTime->SetText( ss.str(), Color::Green, 30 );
}

void HUD::SetStatusText(const std::string& text, float duration /* = -1.0f */)
{
    mTextStatus->SetText(text, Color::Red, 56);
    
    mGame.GetGameTimers().ClearAllTimers(this);
    if (duration > 0.0f)
    {
        TimerHandle timer;
        mGame.GetGameTimers().SetTimer(timer, this, &HUD::ClearStatusText, duration);
    }
}

void HUD::ClearStatusText()
{
    mTextStatus->SetText("", Color::Red, 56);
}

