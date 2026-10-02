#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D container;

void main()
{
    float ambientStrength = 0.1f;
    vec3 ambi
    FragColor = texture(container, TexCoord);
}