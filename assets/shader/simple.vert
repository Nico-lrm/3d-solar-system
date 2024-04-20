#version 430 core

layout(location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 viewProj;
uniform float near;
uniform float far;


void main()
{
	gl_Position = viewProj * model * vec4(position, 1.0);
    //gl_Position.z = 2.0*log(gl_Position.w/near)/log(far/near) - 1; 
    //gl_Position.z *= gl_Position.w;
}