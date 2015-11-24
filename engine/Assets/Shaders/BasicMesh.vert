// Sprite.vert
// Vertex shader for texture mapped meshes

#version 330 core

uniform mat4 uViewProj;
uniform mat4 uWorldTransform;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

out vec4 outWorldPos;
out vec4 outNormal;
out vec2 outTexCoord;

void main()
{
	// Just propagate the texture coordinates
	outTexCoord = inTexCoord;

	// Transform normal into world space
	outNormal = uWorldTransform * vec4(inNormal, 0.0f);
	
	// Transform position into world space
	outWorldPos =  uWorldTransform * vec4(inPosition, 1.0f);
	// Now into projection space
	gl_Position = uViewProj * outWorldPos;
}
