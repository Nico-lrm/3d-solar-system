#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

layout(std430, binding = 0) buffer bufferModelMatrices
{
    mat4 models[];
};

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;


out mat3 TBN;
out vec3 T;
out vec3 B;
out vec3 N;
out mat3 normalMatrix;

out vec3 TangentLightPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;

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

uniform mat4 view;
uniform mat4 proj;
uniform vec3 cameraPos;
uniform int reverse_normal;
uniform float near;
uniform float far;

void main()
{
    FragPos = vec3((models[gl_InstanceID] * vec4(aPos, 1.0) + vec4(cameraPos, 0.0)));
    Normal = transpose(inverse(mat3(models[gl_InstanceID]))) * aPos;
    TexCoords = aTexCoords;

    normalMatrix = transpose(inverse(mat3(models[gl_InstanceID])));
    T = normalize(normalMatrix * aTangent);
    N = normalize(Normal);
    B = cross(T, N);
    T = normalize(T - dot(T, N) * N);

    TBN = transpose(mat3(T, B, N));
    TangentLightPos = TBN * pLight.position;
    TangentViewPos = TBN * cameraPos;
    TangentFragPos = TBN * FragPos;

    gl_Position = proj * view * models[gl_InstanceID] * vec4(aPos, 1.0);
    //gl_Position.z = 2.0*log(gl_Position.w/near)/log(far/near) - 1; 
    //gl_Position.z *= gl_Position.w;
}
