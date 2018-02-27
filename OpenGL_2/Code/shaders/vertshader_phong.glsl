#version 330 core

// Define constants
#define M_PI 3.141593

// Inputs
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertNormal_in;

// Uniforms
uniform mat4 modelTransform;
uniform mat4 perspectiveTransform;
uniform mat3 normalTransform;

// Outputs
out vec3 vertNormal;
out vec3 position_out;


void main()
{
    vec4 position = (modelTransform * vec4(vertCoordinates_in,1));

    // gl_Position is the output (a vec4) of the vertex shader
    gl_Position = perspectiveTransform * position;

    vertNormal = normalTransform * vertNormal_in;
    position_out = position.xyz;
}
