#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

out vec3 TangentLightPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;
out mat3 TBN;
out vec3 T;
out vec3 B;
out vec3 N;
out mat3 normalMatrix;

out vec3 v_viewPosition;

struct PointLight
{
    // Position de la lumière
    vec3 position;

    // Couleur ambiante, de diffusion et de réflexion de la lumière
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform PointLight pLight;
uniform int isEmissive;

uniform mat4 proj;
uniform mat4 modelview;
uniform mat4 model;
uniform mat4 view;
uniform mat3 normals;
uniform vec3 cameraPos;
uniform float near;
uniform float far;
uniform int reverse_normal;

void main()
{
    FragPos = vec3((model * vec4(aPos, 1.0) + vec4(cameraPos, 0.0)));
    Normal = normals * aPos;
    TexCoords = aTexCoords;

    normalMatrix = transpose(inverse(mat3(model)));
    T = normalize(normalMatrix * aTangent);
    N = normalize(Normal);;
    B = cross(T, N);
    T = normalize(T - dot(T, N) * N);

    // Si les modeles ont des UV symetrique
    if (dot(cross(N, T), B) < 0.0)
        T = T * -1.0;

    TBN = transpose(mat3(T, B, N));
    TangentLightPos = TBN * pLight.position;
    TangentViewPos = TBN * cameraPos;
    TangentFragPos = TBN * FragPos;

    vec4 viewPosition = modelview * vec4(aPos, 1.0);
    v_viewPosition = viewPosition.xyz / viewPosition.w;

    gl_Position = proj * modelview * (vec4(aPos, 1.0));
    //gl_Position.z = 2.0*log(gl_Position.w/near)/log(far/near) - 1; 
    //gl_Position.z *= gl_Position.w;
}
