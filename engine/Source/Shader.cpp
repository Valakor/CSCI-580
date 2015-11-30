#include "Shader.h"
#include <fstream>
#include <sstream>
#include <SDL/SDL.h>

Shader::Shader()
	:mVertexShader( 0 )
	, mFragmentShader( 0 )
	, mShaderProgram( 0 )
	, bIsInstance(false)
{

}

Shader::~Shader()
{
	if (!bIsInstance)
	{
		glDeleteProgram(mShaderProgram);
		glDeleteShader(mVertexShader);
		glDeleteShader(mFragmentShader);
	}
}

void Shader::SetActive()
{
	glUseProgram( mShaderProgram );
}

void Shader::SetDefaultAttributes()
{
	mAmbientColor = Vector3(0.1f, 0.1f, 0.1f);
	mEmissiveColor = Vector3(0, 0, 0);
	mDiffuseColor = Vector3(1, 1, 1);
	mSpecularColor = Vector3(1, 1, 1);
	mSpecularPower = 16.0f;
}

ShaderPtr Shader::CreateShaderInstance()
{
	auto instance = std::make_shared<Shader>(*this);
	instance->bIsInstance = true;
	return instance;
}

void Shader::BindViewProjection( const Matrix4& viewProj )
{
	mMatrixBlock.mViewProj = viewProj;
}

void Shader::BindWorldTransform( const Matrix4& worldTransform )
{
	mMatrixBlock.mWorldTransform = worldTransform;
}

void Shader::UploadUniformsToGPU()
{
	GLuint view = glGetUniformLocation( mShaderProgram, "uViewProj" );
	glUniformMatrix4fv( view, 1, GL_FALSE, mMatrixBlock.mViewProj.GetAsFloatPtr() );
	GLuint world = glGetUniformLocation( mShaderProgram, "uWorldTransform" );
	glUniformMatrix4fv( world, 1, GL_FALSE, mMatrixBlock.mWorldTransform.GetAsFloatPtr() );
	
	BindUniformVector3("EyePosW", cameraPos, 1.0f);
	BindUniformVector3("LightPosW", lightPos, 1.0f);
	BindUniformVector3("LightColor", lightColor, 1.0f);

	BindUniformVector3("Ambient", mAmbientColor, 1.0f);
	BindUniformVector3("MaterialEmissive", mEmissiveColor, 1.0f);
	BindUniformVector3("MaterialDiffuse", mDiffuseColor, 1.0f);
	BindUniformVector3("MaterialSpecular", mSpecularColor, 1.0f);
	BindUniformFloat("MaterialShininess", mSpecularPower);
}

void Shader::BindTexture( const char* param, TexturePtr texture, int unit )
{
	glActiveTexture( GL_TEXTURE0 );
	texture->SetActive();

	// We want to wrap textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	GLuint uniform = glGetUniformLocation( mShaderProgram, param );
	glUniform1i( uniform, unit );
}

bool Shader::BindUniformVector3(const std::string& name, const Vector3& input, float w)
{
	int glLoc = glGetUniformLocation(mShaderProgram, name.c_str());
	if (glLoc >= 0)
	{
		glUniform4f(glLoc, input.x, input.y, input.z, w);
		return true;
	}

	return false;
}

bool Shader::BindUniformFloat(const std::string& name, float input)
{
	int glLoc = glGetUniformLocation(mShaderProgram, name.c_str());
	if (glLoc >= 0)
	{
		glUniform1f(glLoc, input);
		return true;
	}

	return false;
}

bool Shader::Load( const char* fileName, class AssetCache* cache )
{
	// Shaders are specified without the extension, we need to add them...
	std::string fileStr( fileName );

	// Vertex shader
	std::ifstream vertexFile( fileStr + ".vert" );
	if ( vertexFile.is_open() )
	{
		std::stringstream sstream;
		sstream << vertexFile.rdbuf();
		mVertexShader = glCreateShader( GL_VERTEX_SHADER );
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();
		glShaderSource( mVertexShader, 1, &(contentsChar), nullptr );
		glCompileShader( mVertexShader );

		if ( !IsCompiled( mVertexShader ) )
		{
			SDL_Log( "Failed to compile vertex shader for %s", fileName );
			return false;
		}
	}
	else
	{
		SDL_Log( "File not found: Vertex shader for %s", fileName );
		return false;
	}

	// Fragment shader
	std::ifstream fragFile( fileStr + ".frag" );
	if ( fragFile.is_open() )
	{
		std::stringstream sstream;
		sstream << fragFile.rdbuf();
		mFragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();
		glShaderSource( mFragmentShader, 1, &(contentsChar), nullptr );
		glCompileShader( mFragmentShader );

		if ( !IsCompiled( mFragmentShader ) )
		{
			SDL_Log( "Failed to compile fragment shader for %s", fileName );
			return false;
		}
	}
	else
	{
		SDL_Log( "File not found: Fragment shader for %s", fileName );
		return false;
	}

	// Now make the combined shader program
	mShaderProgram = glCreateProgram();
	glAttachShader( mShaderProgram, mVertexShader );
	glAttachShader( mShaderProgram, mFragmentShader );
	// assume that the fragment shader always uses "outColor" as the output
	glBindFragDataLocation( mShaderProgram, 0, "outColor" );
	glLinkProgram( mShaderProgram );

	if ( !IsValidProgram() )
	{
		SDL_Log( "Shader program %s is invalid.", fileName );
		return false;
	}

	SetDefaultAttributes();

	return true;
}

bool Shader::IsCompiled( GLuint shader )
{
	GLint status;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &status );

	if ( status != GL_TRUE )
	{
		char buffer[512];
		memset( buffer, 0, 512 );
		glGetShaderInfoLog( shader, 512, nullptr, buffer );
		SDL_Log( "GLSL Compile Failed:\n%s", buffer );
		return false;
	}

	return true;
}

bool Shader::IsValidProgram()
{
	char buffer[512];
	memset( buffer, 0, 512 );

	GLint status;
	glGetProgramiv( mShaderProgram, GL_LINK_STATUS, &status );
	if ( status != GL_TRUE )
	{
		glGetProgramInfoLog( mShaderProgram, 512, nullptr, buffer );
		SDL_Log( "GLSL Link Status:\n%s", buffer );
		return false;
	}

	return true;
}
