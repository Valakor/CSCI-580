//
//  InputComponent.cpp
//  Game-mac
//
//  Created by Matthew Pohlmann on 8/2/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "InputComponent.h"
#include "Actor.h"
#include "Game.h"
#include "InputManager.h"

IMPL_COMPONENT(InputComponent, MoveComponent);

InputComponent::InputComponent(Actor& owner) : Super(owner)
{
    
}

void InputComponent::BindLinearAxis(const std::string& name)
{
    mOwner.GetGame().GetInput().BindAxis(name, this, &InputComponent::OnLinearAxis);
}

void InputComponent::BindYawAxis(const std::string& name)
{
    mOwner.GetGame().GetInput().BindAxis(name, this, &InputComponent::OnYawAxis);
}

void InputComponent::BindPitchAxis( const std::string& name )
{
	mOwner.GetGame().GetInput().BindAxis( name, this, &InputComponent::OnPitchAxis );
}

void InputComponent::OnLinearAxis(float value)
{
    SetLinearAxis(value);
}

void InputComponent::OnYawAxis(float value)
{
    SetYawAxis(value);
}

void InputComponent::OnPitchAxis( float value )
{
	SetPitchAxis( value );
}
