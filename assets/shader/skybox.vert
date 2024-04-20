#version 430 core
layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 modelviewproj;
uniform vec3 cameraPos;

void main()
{
    TexCoords = aPos;
    vec4 pos = modelviewproj * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}
