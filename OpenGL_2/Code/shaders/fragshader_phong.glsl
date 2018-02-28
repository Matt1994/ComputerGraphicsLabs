#version 330 core

// Define constants
#define M_PI 3.141593

// Inputs
in vec3 vertNormal;
in vec2 texture_out;
in vec3 position_out;
in vec3 lightPosition_transform;

// Uniforms
uniform vec3 lightColor;
uniform vec3 materialIntensity;
uniform vec3 materialColor;
uniform int phongExponent;
uniform sampler2D texSampler;

// Output
out vec4 fColor;

void main()
{
    vec3 eyePos = vec3(0.0,0.0,0.0);

    vec3 N = normalize(vertNormal);
    vec3 L = normalize(lightPosition_transform - position_out);
    vec3 V = normalize(eyePos - position_out);
    vec3 R = normalize((2*dot(N,L)*N) - L);

    vec3 amb     = materialColor * materialIntensity.x;
    vec3 diffuse = max(0.0, dot(L,N)) * materialColor * lightColor * materialIntensity.y;
    vec3 spec    = pow(max(0.0, dot(R,V)),phongExponent) * lightColor * materialIntensity.z;

    vec4 textureColor = texture2D(texSampler, texture_out);

    fColor       = vec4((amb + diffuse + spec),1) * textureColor;
}
