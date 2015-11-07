//
//  CameraComponent.cpp
//  Game-windows
//
//  Created by Matthew Pohlmann on 11/5/15.
//  Copyright (c) 2015 Sanjay Madhav. All rights reserved.
//

#include "CameraComponent.h"
#include "Actor.h"
#include "Renderer.h"
#include "Game.h"

IMPL_COMPONENT( CameraComponent, Component );

CameraComponent::CameraComponent( Actor& owner ) : Super( owner )
	, mHorizontalFollowDistMin(0.0f)
	, mHorizontalFollowDistMax(0.0f)
	, mVerticalFollowDist(0.0f)
	, mTargetOffset(0.0f)
	, mPos(Vector3::Zero)
	, mVelocity(Vector3::Zero)
{

}

void CameraComponent::Tick( float deltaTime )
{
	Super::Tick( deltaTime );

	CalculateTruePosition( deltaTime );
	UpdateViewMatrix();
}

void CameraComponent::SetSpringConstant( float constant )
{
	mSpringConstant = constant;
	mDampingConstant = 2.0f * Math::Sqrt( mSpringConstant );
}

void CameraComponent::SnapToIdealPosition()
{
	mPos = GetIdealPosition();
	mVelocity = Vector3::Zero;
	UpdateViewMatrix();
}

Vector3 CameraComponent::GetIdealPosition()
{
	const Vector3 position = mOwner.GetPosition();
	const Vector3 forward = mOwner.GetWorldTransform().GetXAxis();
	const Vector3 up = mOwner.GetWorldTransform().GetZAxis();

	return position - forward * mHorizontalFollowDistMin + up * mVerticalFollowDist;
}

void CameraComponent::CalculateTruePosition( float deltaTime )
{
	const Vector3 displacement = mPos - GetIdealPosition();
	const Vector3 springAccel = (-mSpringConstant * displacement) - (mDampingConstant * mVelocity);

	mVelocity += springAccel * deltaTime;
	mPos += mVelocity * deltaTime;
}

void CameraComponent::UpdateViewMatrix()
{
	const Vector3 position = mOwner.GetPosition();
	const Vector3 forward = mOwner.GetWorldTransform().GetXAxis();
	const Vector3 left = mOwner.GetWorldTransform().GetYAxis();

	Vector3 lookAt = position + forward * mTargetOffset;

	Vector3 cameraForward = Normalize( lookAt - mPos );
	Vector3 cameraUp = Cross( cameraForward, left );

	Matrix4 viewMat = Matrix4::CreateLookAt( mPos, lookAt, cameraUp );
	mOwner.GetGame().GetRenderer().UpdateViewMatrix( viewMat );
}
