#version 330 core

// Define constants
#define M_PI 3.141593

// Inputs
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertNormal_in;
layout (location = 2) in vec2 vertTexture_in;

// Uniforms
uniform mat4 modelTransform;
uniform mat4 perspectiveTransform;
uniform mat3 normalTransform;
<<<<<<< HEAD
uniform vec3 lightPosition;
=======
>>>>>>> master

// Outputs
out vec3 vertNormal;
out vec3 position_out;
<<<<<<< HEAD
out vec3 lightPosition_transform;
=======
>>>>>>> master
out vec2 texture_out;


void main()
{
    vec4 position = (modelTransform * vec4(vertCoordinates_in,1));

    // gl_Position is the output (a vec4) of the vertex shader
    gl_Position = perspectiveTransform * position;

    vertNormal = normalTransform * vertNormal_in;
    position_out = position.xyz;
    texture_out = vertTexture_in;
<<<<<<< HEAD
    lightPosition_transform = vec4(modelTransform * vec4(lightPosition,1)).xyz;
=======
>>>>>>> master
}
