#version 430 core

// Basé sur l'article d'Alexander Christensen sur la technique présenté à ACM Siggraph 2014 par Jorge Jimenez
// https://learnopengl.com/Guest-Articles/2022/Phys.-Based-Bloom

uniform sampler2D srcTexture;
uniform float filterRadius;

in vec2 TexCoords;
layout (location = 0) out vec3 upsample;

void main()
{
    // L'offset est récupérer grâce au filterRadius passé en paramètre du Bloom
    float x = filterRadius;
    float y = filterRadius;

    // On applique la texture sur les 9 texels (e est le centre de notre affichage)
    // a - b - c
    // d - e - f
    // g - h - i
    vec3 a = texture(srcTexture, vec2(TexCoords.x - x, TexCoords.y + y)).rgb;
    vec3 b = texture(srcTexture, vec2(TexCoords.x,     TexCoords.y + y)).rgb;
    vec3 c = texture(srcTexture, vec2(TexCoords.x + x, TexCoords.y + y)).rgb;

    vec3 d = texture(srcTexture, vec2(TexCoords.x - x, TexCoords.y)).rgb;
    vec3 e = texture(srcTexture, vec2(TexCoords.x,     TexCoords.y)).rgb;
    vec3 f = texture(srcTexture, vec2(TexCoords.x + x, TexCoords.y)).rgb;

    vec3 g = texture(srcTexture, vec2(TexCoords.x - x, TexCoords.y - y)).rgb;
    vec3 h = texture(srcTexture, vec2(TexCoords.x,     TexCoords.y - y)).rgb;
    vec3 i = texture(srcTexture, vec2(TexCoords.x + x, TexCoords.y - y)).rgb;

    // Appliquer un kernel gaussien
    //  1   | 1 2 1 |
    // -- * | 2 4 2 |
    // 16   | 1 2 1 |
    upsample = e*4.0;
    upsample += (b+d+f+h)*2.0;
    upsample += (a+c+g+i);
    upsample *= 1.0 / 16.0;
}