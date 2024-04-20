#version 430 core
layout(location = 0) out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;

in mat3 TBN;
in vec3 T;
in vec3 B;
in vec3 N;

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_normal1;
    sampler2D texture_specular1;
    float opacity;
};

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
uniform vec3 cameraPos;
uniform int isEmissive;

uniform Material mat;

///////////////////////////////////

uniform samplerCube shadow_texture;
uniform float far_plane;
uniform int enable_shadow;

vec3 gridSamplingDisk[20] = vec3[]
(
    vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1),
    vec3(1, 1, -1), vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
    vec3(1, 1, 0), vec3(1, -1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
    vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(-1, 0, -1),
    vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1)
);

float ShadowCalculation()
{
    vec3 fragToLight = FragPos - pLight.position;
    float currentDepth = length(fragToLight);
    float shadow = 0.0;
    float bias = 0.005;
    int samples = 20;
    float closestDepth = 0.0;
    float viewDistance = length(cameraPos - FragPos);
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    for (int i = 0; i < samples; ++i)
    {
        closestDepth = texture(shadow_texture, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= far_plane;   // dénormaliser la valeur
        if (currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);
    return shadow;
}

vec3 CalcBlinnLight(PointLight light, vec3 normal, vec3 fragPos)
{
    // Ambient
    vec3 ambient = 0.15 * light.ambient;

    // Diffuse
    vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * light.diffuse;

    // Specular
    vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 2048.0);
    vec3 specular = spec * vec3(0.2);

    if(enable_shadow == 1)
    {
        float shadow = ShadowCalculation();
        return (ambient + (1.0 - shadow) * (diffuse + specular));
    }
    else
    {
        return (ambient + diffuse + specular);
    }
}

///////////////////////////////////

//uniform vec3 atmosphereColor;
//uniform float atmosphereIntensity;
//uniform vec3 atmosphericScattering;
//uniform vec3 mieCoefficient;
//uniform vec3 rayleighCoefficient;

//const vec3 atmosphericScattering = vec3(5.8e-7, 13.5e-5, 0.15e-5);
//const vec3 atmosphericScattering = vec3(0.0003, 0.00015, 0.00002);
//const vec3 atmosphericScattering = vec3(9.5e-3, 7.5e-4, 6.25e-4);
//const vec3 atmosphericScattering = vec3(5.5e-3, 1.5e-3, 1.0e-4);    Valeur de reférence basé sur données réelles
//const vec3 atmosphericScattering = vec3(0.00005, 0.00001, 0.00001); // Proche
//const vec3 atmosphericScattering = vec3(0.00000000001, 0.0003, 0.0001); // Test

//const vec3 atmosphericScattering = vec3(0.004, 0.0003, 0.0003); // Moyenne Distance
//const vec3 atmosphereColor = vec3(0.2078, 0.1961, 1.0);
//const vec3 rayleighCoefficient = vec3(5.8e-6, 1.35e-5, 3.31e-5);
//const vec3 mieCoefficient = vec3(2.0e-4, 0.0, 2.0e-4);
const float atmosphereIntensity = 0.05;

uniform vec3 atmosphericScattering;
uniform vec3 atmosphereColor;
uniform vec3 rayleighCoefficient;
uniform vec3 mieCoefficient;


const float pi = 3.1415926535897932384626433832795;
uniform vec3 planetPos;
uniform float planetRadius;
uniform float atmosphereRadius;
uniform int hasAtmosphere;


// Earth
//const vec3 atmosphericScattering = vec3(0.081, 0.1, 0.03);
//const vec3 atmosphereColor = vec3(0.15, 0.15, 0.175);
//const vec3 rayleighCoefficient = vec3(0.65, 2.55, 2.25);
//const vec3 mieCoefficient = vec3(5.0, 4.6, 4);

// Mars
//const vec3 atmosphericScattering = vec3(0.015, 0.008, 0.005);
//const vec3 atmosphereColor = vec3(0.7, 0.3, 0.1);
//const vec3 rayleighCoefficient = vec3(0.85, 2.5, 2.0);
//const vec3 mieCoefficient = vec3(2.0, 2.0, 1.5);

// Jupiter
//const vec3 atmosphericScattering = vec3(0.5, 0.5, 0.5);
//const vec3 atmosphereColor = vec3(0.5, 0.5, 0.5);
//const vec3 rayleighCoefficient = vec3(0.3, 0.3, 0.3);
//const vec3 mieCoefficient = vec3(50.0, 46.0, 40.0);

float scale(float cosTheta)
{
    float x = 1.0 - cosTheta;
    float rayleighPhase = 0.75 * (1.0 + cosTheta * cosTheta);
    float miePhase = 1.5 * ((1.0 - 0.1 * cosTheta) * (1.0 - 0.1 * cosTheta)) / (4.0 * pi);
    return (atmosphericScattering.x * exp(-atmosphericScattering.y * x * x) + (rayleighCoefficient.x * rayleighPhase + mieCoefficient.x * miePhase) * exp(-(atmosphereRadius - planetRadius) * (rayleighCoefficient.y + mieCoefficient.y)));
}

vec3 getAttenuation(vec3 from, vec3 to)
{
    vec3 dir = normalize(to - from);
    float height = length(to - FragPos);
    float cosTheta = dot(dir, to) / height;
    float rayleighPhase = 0.75 * (1.0 + cosTheta * cosTheta);
    float miePhase = 1.5 * ((1.0 - 0.1 * cosTheta) * (1.0 - 0.1 * cosTheta)) / (4.0 * pi);
    float attenuation = scale(cosTheta);
    float innerRadius = planetRadius;
    float innerRadius2 = innerRadius * innerRadius;
    float outerRadius = atmosphereRadius;
    float outerRadius2 = outerRadius * outerRadius;
    float scaleHeight = 1.0 / (outerRadius - innerRadius);
    float rayleighHeight = exp(-(height - innerRadius) * scaleHeight / rayleighCoefficient.y);
    float mieHeight = exp(-(height - innerRadius) * scaleHeight / mieCoefficient.y);
    vec3 attenuationFactor = exp(-(rayleighHeight * rayleighCoefficient + mieHeight * mieCoefficient));
    return attenuationFactor;
}

vec4 atmosphericScatteringShader(vec3 position, vec3 normal)
{
    vec3 toCamera = normalize(cameraPos - position);
    vec3 from = position;
    vec3 to = from + toCamera * atmosphereRadius;

    // Calcul de l'angle de la lumière
    vec3 lightDir = normalize(pLight.position - position);
    float lightAngle = dot(-lightDir, toCamera);
    //vec3 color = mix(atmosphereColor, vec3(0.7451, 0.2745, 0.0), max(0.0, lightAngle - 0.5));
    vec3 color = mix(atmosphereColor, vec3(0.7451, 0.2745, 0.0), 0.9);

    // Calcul de l'angle de vue
    float cosViewAngle = dot(normal, toCamera);
    float angle = acos(lightAngle);
    float angleMultiplier = 0.003;

    float rayleighDecayFactor = 0.1;
    float mieDecayFactor = 3.0;

    // Multiplicateur exponentiel pour le coefficient de Rayleigh
    float rayleighAngleMultiplier = exp(-rayleighDecayFactor * angleMultiplier);

    // Multiplicateur exponentiel pour le coefficient de Mie
    float mieAngleMultiplier = exp(mieDecayFactor * angleMultiplier);

    float rayleighWeight = 0.1;
    float mieWeight = 0.9;
    angleMultiplier = abs(1.0 - lightAngle);

    vec3 rayleighCoefficients = (3.0 / (16.0 * pi)) * atmosphericScattering * (1.0 + cosViewAngle * cosViewAngle);
    vec3 mieCoefficients = (1.0 / (4.0 * pi)) * atmosphericScattering * ((1.0 - atmosphericScattering.z * atmosphericScattering.z) / (1.0 + atmosphericScattering.z * atmosphericScattering.z - 2.0 * atmosphericScattering.z * cosViewAngle));

    vec3 dir = normalize(to - from);
    float cosTheta = dot(dir, to) / (atmosphereRadius - planetRadius);
    float rayleighPhase = 0.75 * (1.0 + cosTheta * cosTheta);
    float miePhase = 1.5 * ((1.0 - 0.1 * cosTheta) * (1.0 - 0.1 * cosTheta)) / (4.0 * pi);

    // Calcul de l'atténuation atmosphérique
    vec3 attenuationFactor = getAttenuation(from, to);
    vec3 attenuation = exp(-(attenuationFactor * (rayleighCoefficients * rayleighPhase + mieCoefficients * miePhase)));

    // Calcul de l'éclairage diffus
    vec3 light = normalize(lightDir);
    float diffuse = max(0.0, dot(normal, light));

    return vec4(color * diffuse * attenuation, 1.0);
}

///////////////////////////////////

void main()
{
    if(isEmissive == 0)
    {
        vec3 color = texture(mat.texture_diffuse1, TexCoords).rgb;
        vec3 normal = texture(mat.texture_normal1, TexCoords).rgb;
        normal = normalize(normal * 2.0 - 1.0);
        vec3 lighting = vec3(0.0);

        lighting = lighting + CalcBlinnLight(pLight, vec3(normal), FragPos);
        color = color * lighting;


        if(hasAtmosphere == 1)
        {
            FragColor = vec4(mix(color, atmosphericScatteringShader(FragPos, Normal).rgb, atmosphereIntensity), mat.opacity);
        }
        else
        {
            FragColor = vec4(color.rgb, mat.opacity);
        }
    }
    else
    {
        vec3 color = vec3(0.9804, 0.9255, 0.6275);
        vec3 finalColor = mix(texture(mat.texture_diffuse1, TexCoords).rgb, color, 0.4) * 50;
        FragColor = vec4(finalColor, mat.opacity);
    }
}