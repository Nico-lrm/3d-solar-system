#version 430 core
layout(location = 0)out vec4 FragColor;

uniform vec3 color;

void main()
{
	FragColor = vec4(color, 0.1f);
}