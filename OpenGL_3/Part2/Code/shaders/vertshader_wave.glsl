#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertNormal_in;
layout (location = 2) in vec2 uv_in;

// Specify the Uniforms of the vertex shader
uniform mat4 modelTransform;
uniform mat4 perspectiveTransform;
uniform mat4 viewTransform;

uniform float amplitude[5];
uniform float frequency[5];
uniform float phase[5];
uniform float time;

// Specify the output of the vertex stage
out vec3 normal;

float waveHeight(int waveIdx, float uvalue){
    return amplitude[waveIdx]*sin((2*M_PI*frequency[waveIdx]*uvalue) + phase[waveIdx] + time);
}

float waveDU(int waveIdx, float uvalue){
    return -amplitude[waveIdx]*2*M_PI*frequency[waveIdx]*cos((2*M_PI*frequency[waveIdx]*uvalue) + phase[waveIdx] + time);
}

void main()
{
    vec3 coords = vertCoordinates_in;

    coords.z = 0;
    normal = vec3(0.0,0.0,1.0);

    for(int i=0;i<5;i++){
        coords.z += waveHeight(i, uv_in.x);
        normal.x += waveDU(i,uv_in.x);
    }

    gl_Position = perspectiveTransform * viewTransform * modelTransform * vec4(coords, 1.0);
    normal = normalize(normal);
}
