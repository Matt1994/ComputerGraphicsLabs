#version 330 core

// Define constants
#define M_PI 3.141593

// Inputs
in vec3 vertNormal;
in vec3 position_out;

// Uniforms
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 materialIntensity;
uniform vec3 materialColor;
uniform int phongExponent;

// Output
out vec4 fColor;

void main()
{
    vec3 eyePos = vec3(0.0,0.0,0.0);

    vec3 N = normalize(vertNormal);
    vec3 L = normalize(lightPosition - position_out);
    vec3 V = normalize(eyePos - position_out);
    vec3 R = normalize((2*dot(N,L)*N) - L);

    vec3 amb     = materialColor * materialIntensity.x;
    vec3 diffuse = max(0.0, dot(L,N)) * materialColor * lightColor * materialIntensity.y;
    vec3 spec    = pow(max(0.0, dot(R,V)),phongExponent) * lightColor * materialIntensity.z;

    fColor       = vec4(amb + diffuse + spec,1);
}
