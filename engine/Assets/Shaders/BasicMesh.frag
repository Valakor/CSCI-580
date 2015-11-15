// Sprite.frag
// Fragment (pixel) shader for texture mapped meshes

#version 330 core

in vec4 outWorldPos;
in vec4 outNormal;
in vec2 outTexCoord;

uniform vec4 EyePosW;   // Eye position in world space.
uniform vec4 LightPosW; // Light's position in world space.
uniform vec4 LightColor; // Light's diffuse and specular contribution.
 
uniform vec4 MaterialEmissive;
uniform vec4 MaterialDiffuse;
uniform vec4 MaterialSpecular;
uniform float MaterialShininess;
 
uniform vec4 Ambient; // Global ambient contribution.

uniform sampler2D uTexture;

out vec4 outColor;

void main()
{
	// Compute the emissive term.
    vec4 Emissive = MaterialEmissive;
 
    // Compute the diffuse term.
    vec4 N = normalize( outNormal );
    vec4 L = normalize( LightPosW - outWorldPos );
    float NdotL = max( dot( N, L ), 0 );
    vec4 Diffuse =  NdotL * LightColor * MaterialDiffuse;
     
    // Compute the specular term.
    vec4 V = normalize( EyePosW - outWorldPos );
    vec4 H = normalize( L + V );
    vec4 R = reflect( -L, N );
    float RdotV = max( dot( R, V ), 0 );
    float NdotH = max( dot( N, H ), 0 );
    vec4 Specular = pow( RdotV, MaterialShininess ) * LightColor * MaterialSpecular;
     
    outColor = ( Emissive + Ambient + Diffuse + Specular ) * texture( uTexture, outTexCoord );
}
