#version 430 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 18) out;

uniform mat4 shadowMatrices[6];
uniform vec3 cameraPos;
out vec4 FragPos; // FragPos émit par le GS

void emitFace(mat4 m) {
    for(int i = 0; i < 3; ++i)
    {
        vec3 adjustedPos = gl_in[i].gl_Position.xyz - cameraPos;
        FragPos = vec4(adjustedPos, 1.0);
        gl_Position = m * FragPos;
        EmitVertex();
    }
    EndPrimitive();
}

void main()
{
    gl_Layer = 0;
    emitFace(shadowMatrices[0]);

    gl_Layer = 1;
    emitFace(shadowMatrices[1]);

    gl_Layer = 2;
    emitFace(shadowMatrices[2]);

    gl_Layer = 3;
    emitFace(shadowMatrices[3]);

    gl_Layer = 4;
    emitFace(shadowMatrices[4]);

    gl_Layer = 5;
    emitFace(shadowMatrices[5]);
}