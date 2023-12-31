#version 430 core

float AMBIENT = 0.1;

uniform vec3 color;
uniform vec3 lightPos;
uniform sampler2D colorTexture;

in vec3 vecNormal;
in vec3 worldPos;
in vec2 vecTextCoord;

out vec4 outColor;
void main()
{
	vec3 lightDir = normalize(lightPos-worldPos);
	vec3 normal = normalize(vecNormal);
	vec4 textureColor = texture2D(colorTexture, vecTextCoord);
	float diffuse=max(0,dot(normal,lightDir));
	outColor = textureColor;
}
