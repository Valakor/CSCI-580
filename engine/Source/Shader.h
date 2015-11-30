// Shader.h
// Shader asset that encapsulates both the vertex
// and fragment shaders

#pragma once
#include "Asset.h"
#include <GL/glew.h>
#include "Math.h"
#include "Texture.h"
#include <string>

class Shader : public Asset
{
	DECL_ASSET( Shader, Asset );
public:
	Shader();
	virtual ~Shader();

	void SetActive();

	void SetDefaultAttributes();

	std::shared_ptr<Shader> CreateShaderInstance();

	// NOTE: Bind functions assume that this shader is active
	void BindViewProjection( const Matrix4& viewProj );
	void BindWorldTransform( const Matrix4& worldTransform );

	void BindCameraPosition(const Vector3& pos) { cameraPos = pos; }
	void BindLightColor(const Vector3& color) { lightColor = color; }
	void BindLightPosition(const Vector3& pos) { lightPos = pos; }

	bool BindAmbientColor(const Vector3& ambient) { mAmbientColor = ambient; }
	bool BindEmissiveColor(const Vector3& emissive) { mEmissiveColor = emissive; }
	bool BindDiffuseColor(const Vector3& diffuse) { mDiffuseColor = diffuse; }
	bool BindSpecularColor(const Vector3& specular) { mSpecularColor = specular; }
	bool BindSpecPower(float power) { mSpecularPower = power; }

	void UploadUniformsToGPU();

	// Bind the specified texture to the specified unit
	void BindTexture( const char* param, TexturePtr texture, int unit );

	GLuint GetShaderProgram() const { return mShaderProgram; }
protected:
	bool BindUniformVector3(const std::string& name, const Vector3& input, float w);
	bool BindUniformFloat(const std::string& name, float input);

	bool Load( const char* fileName, class AssetCache* cache ) override;
	bool IsCompiled( GLuint shader );
	bool IsValidProgram();
private:
	// Used for uniform buffer object format (hard-coded for now)
	struct MatrixBlock
	{
		Matrix4 mViewProj;
		Matrix4 mWorldTransform;
	};

	MatrixBlock mMatrixBlock;
	Vector3 cameraPos;
	Vector3 lightColor;
	Vector3 lightPos;

	Vector3 mAmbientColor;
	Vector3 mEmissiveColor;
	Vector3 mDiffuseColor;
	Vector3 mSpecularColor;
	float mSpecularPower;

	GLuint mVertexShader;
	GLuint mFragmentShader;
	GLuint mShaderProgram;
};

DECL_PTR( Shader );
