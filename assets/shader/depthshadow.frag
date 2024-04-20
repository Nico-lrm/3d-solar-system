#version 430 core
in vec4 FragPos;

uniform vec3 lightPos;
uniform float far_plane;

void main()
{
    float lightDistance = length(FragPos.xyz - lightPos);

    // On dénormalise la distance
    lightDistance = lightDistance / far_plane;

    // On dessine la distance dans la texture du depth_framebuffer
    gl_FragDepth = lightDistance;
}