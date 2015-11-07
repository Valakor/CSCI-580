#include "SpriteComponent.h"
#include "Actor.h"
#include <SDL/SDL.h>
#include "Renderer.h"

IMPL_COMPONENT(SpriteComponent, DrawComponent);

SpriteComponent::SpriteComponent(Actor& owner)
	:DrawComponent(owner)
{

}

void SpriteComponent::Draw(Renderer& render)
{
    if (!mTexture)
    {
        return;
    }
    
    Matrix4 scale = Matrix4::CreateScale(static_cast<float>(mTexture->GetWidth()), static_cast<float>(mTexture->GetHeight()), 1.0f);
    render.DrawSprite(mTexture, scale * mOwner.GetWorldTransform());
}

