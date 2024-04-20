#version 430 core
layout(location = 0) out vec4 FragColor;
in vec3 TexCoords;

uniform samplerCube texture_skybox1;

void main()
{
	//FragColor = vec4(0.5137, 0.5137, 0.5137, 1.0);
	vec3 col = textureLod(texture_skybox1, TexCoords, 0.0).rgb;
	FragColor = vec4(col, 1.0);
}