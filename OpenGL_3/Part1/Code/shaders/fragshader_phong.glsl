#version 330 core

// Define constants
#define M_PI 3.141593

// Inputs
in vec3 vertNormal;
in vec2 texture_out;
in vec3 position_out;

// Uniforms
uniform vec3 materialIntensity;
uniform int phongExponent;
uniform sampler2D texSampler;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 eyePos;

// Output
out vec4 fColor;

void main()
{
    vec4 textureColor = texture2D(texSampler, texture_out);

    vec3 N = normalize(vertNormal);
    vec3 L = normalize(lightPosition - position_out);
    vec3 V = normalize(eyePos - position_out);
    vec3 R = normalize((2*dot(N,L)*N) - L);

    vec3 amb     = textureColor.xyz * materialIntensity.x * lightColor;
    vec3 diffuse = max(0.0, dot(L,N)) * textureColor.xyz * materialIntensity.y * lightColor;
    vec3 spec    = max(0.0, pow(dot(R,V),phongExponent)) * materialIntensity.z * lightColor;

    fColor       = vec4((amb + diffuse + spec),1);
}
