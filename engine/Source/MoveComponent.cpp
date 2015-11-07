#include "MoveComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

IMPL_COMPONENT(MoveComponent, Component);

MoveComponent::MoveComponent(Actor& owner)
	:Component(owner)
	,mLinearSpeed(0.0f)
	,mAngularSpeed(0.0f)
	,mLinearAxis(0.0f)
	,mYawAxis(0.0f)
	,mPitchAxis(0.0f)
{

}

void MoveComponent::Tick(float deltaTime)
{
    if (!Math::IsZero(mYawAxis))
    {
        // Get new rotation
        float deltaAngle = mAngularSpeed * mYawAxis * deltaTime;
		Vector3 rotationAxis = GetOwner().GetWorldTransform().GetZAxis();
		Quaternion deltaRotation = Quaternion( rotationAxis, deltaAngle );
		Quaternion newRotation = Concatenate( GetOwner().GetRotation(), deltaRotation );

        // Update owner's rotation
        mOwner.SetRotation( newRotation );
    }

	if ( !Math::IsZero( mPitchAxis ) )
	{
		// Get new rotation
		float deltaAngle = mAngularSpeed * mPitchAxis * deltaTime;
		Vector3 rotationAxis = GetOwner().GetWorldTransform().GetYAxis();
		Quaternion deltaRotation = Quaternion( rotationAxis, deltaAngle );
		Quaternion newRotation = Concatenate( GetOwner().GetRotation(), deltaRotation );

		// Update owner's rotation
		mOwner.SetRotation( newRotation );
	}
    
    
    if (!Math::IsZero(mLinearAxis))
    {
        // Update velocity based on current forward
        Vector3 velocity = mOwner.GetForward() * mLinearSpeed * mLinearAxis;
        
        // Get new position
        Vector3 position = mOwner.GetPosition() + velocity * deltaTime;
        
        // Update owner's position
        mOwner.SetPosition(position);
    }
}

void MoveComponent::AddToLinearAxis(float delta)
{
	mLinearAxis += delta;
	mLinearAxis = Math::Clamp(mLinearAxis, -1.0f, 1.0f);
}

void MoveComponent::AddToYawAxis(float delta)
{
	mYawAxis += delta;
	mYawAxis = Math::Clamp( mYawAxis, -1.0f, 1.0f );
}

void MoveComponent::AddToPitchAxis( float delta )
{
	mPitchAxis += delta;
	mPitchAxis = Math::Clamp( mPitchAxis, -1.0f, 1.0f );
}

void MoveComponent::SetLinearAxis(float axis)
{
	mLinearAxis = Math::Clamp(axis, -1.0f, 1.0f);
}

void MoveComponent::SetYawAxis(float axis)
{
	mYawAxis = Math::Clamp( axis, -1.0f, 1.0f );
}

void MoveComponent::SetPitchAxis( float axis )
{
	mPitchAxis = Math::Clamp( axis, -1.0f, 1.0f );
}
