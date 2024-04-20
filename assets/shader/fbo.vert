#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec2 TexCoords;
out vec2 pos;

void main()
{
    TexCoords = aTexCoords;
    pos=aPos.xy;
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
}