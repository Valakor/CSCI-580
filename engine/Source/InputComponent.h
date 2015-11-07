//
//  InputComponent.h
//  Game-mac
//
//  Created by Matthew Pohlmann on 8/2/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "MoveComponent.h"
#include <string>

class InputComponent : public MoveComponent
{
    DECL_COMPONENT(InputComponent, MoveComponent);
    
public:
    
    InputComponent(Actor& owner);
    
    void BindLinearAxis(const std::string& name);
    void BindYawAxis(const std::string& name);
	void BindPitchAxis( const std::string& name );
    
protected:
    
    void OnLinearAxis(float value);
    void OnYawAxis(float value);
	void OnPitchAxis( float value );
    
};

DECL_PTR(InputComponent);
