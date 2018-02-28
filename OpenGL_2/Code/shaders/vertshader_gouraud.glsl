#version 330 core

// Define constants
#define M_PI 3.141593

// Input locations
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertNormal_in;
layout (location = 2) in vec2 vertTexture_in;

// Uniforms
uniform mat4 modelTransform;
uniform mat4 perspectiveTransform;
uniform mat3 normalTransform;
uniform vec3 lightPosition;
uniform vec3 materialIntensity;
uniform int phongExponent;

// Output
out vec3 vertIntensity;
out vec2 texture_out;

void main()
{
    vec4 position = modelTransform * vec4(vertCoordinates_in, 1.0);
    vec3 lightPosition_transform = vec4(modelTransform*vec4(lightPosition,1)).xyz;

    // gl_Position is the output (a vec4) of the vertex shader
    gl_Position = perspectiveTransform * position;

    vec3 eyePos = vec3(0.0,0.0,0.0);

    vec3 N = normalize(normalTransform * vertNormal_in);
    vec3 L = normalize(lightPosition_transform - position.xyz);
    vec3 V = normalize(eyePos - position.xyz);
    vec3 R = normalize((2*dot(N,L)*N) - L);
    vec3 H = normalize(L + V);

    vec3 amb     = vec3(materialIntensity.x);
    vec3 diffuse = vec3(max(0.0, dot(L,N)) * materialIntensity.y);
    vec3 spec    = vec3(pow(max(0.0,dot(N,H)),phongExponent) * materialIntensity.z);

    vertIntensity = amb + diffuse + spec;
    texture_out = vertTexture_in;
}
