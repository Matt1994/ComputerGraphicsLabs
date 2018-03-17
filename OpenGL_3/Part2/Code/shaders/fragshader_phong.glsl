#version 330 core

// Define constants
#define M_PI 3.141593

// Inputs
in vec3 vertNormal;
in vec3 position_out;
in vec3 materialColor;

// Uniforms
uniform vec3 materialIntensity;
uniform int phongExponent;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 eyePos;

// Output
out vec4 fColor;

void main()
{
    vec3 N = normalize(vertNormal);
    vec3 L = normalize(lightPosition - position_out);
    vec3 V = normalize(eyePos - position_out);
    vec3 R = normalize((2*dot(N,L)*N) - L);

    vec3 amb     = materialColor * materialIntensity.x * lightColor;
    vec3 diffuse = max(0.0, dot(L,N)) * materialColor * materialIntensity.y * lightColor;
    vec3 spec    = max(0.0, pow(dot(R,V),phongExponent)) * materialIntensity.z * lightColor;

    fColor       = vec4((amb + diffuse + spec),1);
}
