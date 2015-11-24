#include "Shader.h"
#include <fstream>
#include <sstream>
#include <SDL/SDL.h>

Shader::Shader()
	:mVertexShader( 0 )
	, mFragmentShader( 0 )
	, mShaderProgram( 0 )
{

}

Shader::~Shader()
{
	glDeleteProgram( mShaderProgram );
	glDeleteShader( mVertexShader );
	glDeleteShader( mFragmentShader );
}

void Shader::SetActive()
{
	glUseProgram( mShaderProgram );
}

void Shader::BindViewProjection( const Matrix4& viewProj )
{
	mMatrixBlock.mViewProj = viewProj;
}

void Shader::BindWorldTransform( const Matrix4& worldTransform )
{
	mMatrixBlock.mWorldTransform = worldTransform;
}

void Shader::BindAmbientColor(const Vector3& ambient)
{
	GLuint ambientLoc = glGetUniformLocation(mShaderProgram, "Ambient");
	glUniform4f(ambientLoc, ambient.x, ambient.y, ambient.z, 1.0f);
}

void Shader::BindEmissiveColor(const Vector3& emissive)
{
	GLuint emissiveLoc = glGetUniformLocation(mShaderProgram, "MaterialEmissive");
	glUniform4f(emissiveLoc, emissive.x, emissive.y, emissive.z, 1.0f);
}

void Shader::BindDiffuseColor(const Vector3& diffuse)
{
	GLuint diffuseLoc = glGetUniformLocation(mShaderProgram, "MaterialDiffuse");
	glUniform4f(diffuseLoc, diffuse.x, diffuse.y, diffuse.z, 1.0f);
}

void Shader::BindSpecularColor(const Vector3& specular)
{
	GLuint specLoc = glGetUniformLocation(mShaderProgram, "MaterialSpecular");
	glUniform4f(specLoc, specular.x, specular.y, specular.z, 1.0f);
}

void Shader::BindSpecPower(float power)
{
	GLuint specPower = glGetUniformLocation(mShaderProgram, "MaterialShininess");
	glUniform1f(specPower, power);
}

void Shader::UploadUniformsToGPU()
{
	//// Bind this buffer to index 0
	//glBindBuffer(GL_UNIFORM_BUFFER, mUniformBuffer);
	//glBindBufferBase(GL_UNIFORM_BUFFER, 0, mUniformBuffer);
	//
	//// Copy uniform buffer data
	//GLvoid* p = glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(mMatrixBlock),
	//				 GL_MAP_INVALIDATE_BUFFER_BIT|GL_MAP_WRITE_BIT);
	//memcpy(p, &mMatrixBlock, sizeof(mMatrixBlock));
	//glUnmapBuffer(GL_UNIFORM_BUFFER);

	GLuint view = glGetUniformLocation( mShaderProgram, "uViewProj" );
	glUniformMatrix4fv( view, 1, GL_FALSE, mMatrixBlock.mViewProj.GetAsFloatPtr() );
	GLuint world = glGetUniformLocation( mShaderProgram, "uWorldTransform" );
	glUniformMatrix4fv( world, 1, GL_FALSE, mMatrixBlock.mWorldTransform.GetAsFloatPtr() );
	
	GLuint camera = glGetUniformLocation(mShaderProgram, "EyePosW");
	glUniform4f(camera, cameraPos.x, cameraPos.y, cameraPos.z, 1.0f);
	GLuint light = glGetUniformLocation(mShaderProgram, "LightPosW");
	glUniform4f(light, lightPos.x, lightPos.y, lightPos.z, 1.0f);
	GLuint lightC = glGetUniformLocation(mShaderProgram, "LightColor");
	glUniform4f(lightC, lightColor.x, lightColor.y, lightColor.z, 1.0f);
}

void Shader::BindTexture( const char* param, TexturePtr texture, int unit )
{
	glActiveTexture( GL_TEXTURE0 );
	texture->SetActive();

	GLuint uniform = glGetUniformLocation( mShaderProgram, param );
	glUniform1i( uniform, unit );
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

	SetActive();

	//// Now setup the uniform buffer object
	//glGenBuffers(1, &mUniformBuffer);
	//glBindBuffer(GL_UNIFORM_BUFFER, mUniformBuffer);
	//glBufferData(GL_UNIFORM_BUFFER, sizeof(mMatrixBlock), &mMatrixBlock, GL_DYNAMIC_DRAW);

	//// Bind it to the program
	//GLuint block = glGetUniformBlockIndex(mShaderProgram, "MatrixBlock");
	//glUniformBlockBinding(mShaderProgram, block, 0);
	//glBindBufferBase(GL_UNIFORM_BUFFER, 0, mUniformBuffer);

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

	//	glValidateProgram(mShaderProgram);
	//	glGetProgramiv(mShaderProgram, GL_VALIDATE_STATUS, &status);
	//	if (status != GL_TRUE)
	//	{
	//		glGetProgramInfoLog(mShaderProgram, 512, nullptr, buffer);
	//		SDL_Log("GLSL Validate Status:\n%s", buffer);
	//		// If this is just a warning, don't die
	//		if (buffer[0] != 'W')
	//		{
	//			return false;
	//		}
	//	}
	return true;
}