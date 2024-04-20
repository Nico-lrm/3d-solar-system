#version 430 core
out vec4 FragColor;

in vec2 TexCoords;
in vec2 pos;

uniform sampler2D render_texture;
uniform sampler2D bright_texture;


vec3 tonemapACES(in vec3 color) {
    float a = 2.51;
    float b = 0.03;
    float c = 2.43;
    float d = 0.59;
    float e = 0.14;
    return clamp((color * (a * color + b)) / (color * (c * color + d) + e), 0.0, 1.0);
}

void main()
{
    const float gamma = 1.0;
    const float exposure = 1.0;    

    vec3 color =  texture(render_texture, TexCoords).xyz;
    vec3 bloom = texture(bright_texture, TexCoords).xyz;
    color = mix(color, bloom, 0.04);
    color = vec3(1.0) - exp(-color * exposure);
    color = pow(color, vec3(1.0 / gamma));
    color = tonemapACES(color);

    FragColor = vec4(color, 1.0);
}