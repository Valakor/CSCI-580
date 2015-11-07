//
//  CameraComponent.h
//  Game-windows
//
//  Created by Matthew Pohlmann on 11/5/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "Component.h"
#include "Math.h"

class CameraComponent : public Component
{
	DECL_COMPONENT( CameraComponent, Component );

public:

	CameraComponent( Actor& owner );

	virtual void Tick( float deltaTime ) override;

	void SetMinHorizontalFollowDistance( float dist ) { mHorizontalFollowDistMin = dist; }
	void SetMaxHorizontalFollowDistance( float dist ) { mHorizontalFollowDistMax = dist; }
	void SetVerticalFollowDistance( float dist ) { mVerticalFollowDist = dist; }
	void SetTargetOffset( float offset ) { mTargetOffset = offset; }

	void SnapToIdealPosition();

	void SetSpringConstant( float constant );

private:

	Vector3 GetIdealPosition();
	void CalculateTruePosition( float deltaTime );
	void UpdateViewMatrix();

	float mHorizontalFollowDistMin;
	float mHorizontalFollowDistMax;
	float mVerticalFollowDist;
	float mTargetOffset;

	Vector3 mPos;
	Vector3 mVelocity;

	float mSpringConstant;
	float mDampingConstant;

};

DECL_PTR( CameraComponent );
