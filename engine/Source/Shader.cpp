#include "Shader.h"
#include <fstream>
#include <sstream>
#include <SDL/SDL.h>
#include "ShaderCache.h"

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

bool Shader::BindAmbientColor(const Vector3& ambient)
{
	return BindUniformVector3("Ambient", ambient, 1.0f);
}

bool Shader::BindEmissiveColor(const Vector3& emissive)
{
	return BindUniformVector3("MaterialEmissive", emissive, 1.0f);
}

bool Shader::BindDiffuseColor(const Vector3& diffuse)
{
	return BindUniformVector3("MaterialDiffuse", diffuse, 1.0f);
}

bool Shader::BindSpecularColor(const Vector3& specular)
{
	return BindUniformVector3("MaterialSpecular", specular, 1.0f);
}

bool Shader::BindSpecPower(float power)
{
	return BindUniformFloat("MaterialShininess", power);
}

void Shader::UploadUniformsToGPU()
{
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

	// add to the game shader cache
	if (!ShaderCache::Get().RegisterShader(fileName, ThisPtr()))
	{
		SDL_Log("Shader program %s already registered in shader cache.", fileName);
		return false;
	}

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