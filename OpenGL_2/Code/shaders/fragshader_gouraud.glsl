#version 330 core

// Define constants
#define M_PI 3.141593

// Input
in vec3 vertColor;
in vec2 texture_out;

// Uniforms
uniform sampler2D texSampler;

// Output
out vec4 fColor;

void main()
{
    vec4 textureColor = texture2D(texSampler, texture_out);
    fColor = vec4(vertColor,1) * textureColor;
}
