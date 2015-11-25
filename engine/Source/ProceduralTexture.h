//
//  ProceduralTexture.h
//  Game-mac
//
//  Created by Ricardo Sisnett on 11/17/15.
//

#include "Texture.h"
#ifndef __Game_mac__ProceduralTexture__
#define __Game_mac__ProceduralTexture__

class ProceduralTexture : public Texture
{
    DECL_ASSET(ProceduralTexture, Texture);
public:
    ProceduralTexture() : Texture(), channels(1), image(nullptr) {}
	virtual ~ProceduralTexture() { if (image) delete[] image; Texture::~Texture();}
	float GetNoise(float u, float v);
protected:
    bool Load(const char* fileName, class AssetCache* cache) override;
	int channels;

private:
	unsigned char* image;
};

DECL_PTR(ProceduralTexture)
#endif /* defined(__Game_mac__ProceduralTexture__) */
