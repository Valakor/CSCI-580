#pragma once
#include "Asset.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include <vector>

class Mesh : public Asset
{
	DECL_ASSET(Mesh, Asset);
public:
	Mesh();
	virtual ~Mesh();

	bool Load(const char* fileName, class AssetCache* cache) override;

	VertexArrayPtr GetVertexArray() { return mVertexArray; }
	TexturePtr GetTexture(size_t index);

	void SetShader(ShaderPtr shader) { mShader = shader; }
	ShaderPtr GetShader() const { return mShader; }

	float GetRadius() const { return mRadius; }
protected:
	VertexArrayPtr mVertexArray;
	std::vector<TexturePtr> mTextures;
	ShaderPtr mShader;
	float mRadius;
};

DECL_PTR(Mesh);
