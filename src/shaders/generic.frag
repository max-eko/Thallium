#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D container;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 viewPos;

uniform float ambientStrength;
uniform float roughness;

uniform int specularExponent;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * roughness;

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularExponent);
    vec3 specular = (1.0 - roughness) * spec * lightColor;

    vec3 rawColor = vec3(texture(container, TexCoord));

    FragColor = vec4((rawColor * ambientStrength) + (rawColor * (diffuse + specular)), 1.0);
}