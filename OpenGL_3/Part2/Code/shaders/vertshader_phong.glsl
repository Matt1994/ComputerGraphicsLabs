#version 330 core

// Define constants
#define M_PI 3.141593

// Inputs
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertNormal_in;
layout (location = 2) in vec2 uv_in;

// Uniforms
uniform mat4 modelTransform;
uniform mat4 perspectiveTransform;
uniform mat4 viewTransform;

uniform float amplitude[5];
uniform float frequency[5];
uniform float phase[5];
uniform float time;

// Outputs
out vec3 vertNormal;
out vec3 position_out;
out vec3 materialColor;

float waveHeight(int waveIdx, float uvalue){
    return amplitude[waveIdx]*sin((2*M_PI*frequency[waveIdx]*uvalue) + (phase[waveIdx]+time));
}

float waveDU(int waveIdx, float uvalue){
    return -amplitude[waveIdx]*2*M_PI*frequency[waveIdx]*cos((2*M_PI*frequency[waveIdx]*uvalue) + (phase[waveIdx]+time));
}

void main()
{
    vec3 coords = vertCoordinates_in;
    coords.z = 0.0;
    vertNormal = vec3(0.0,0.0,1.0);
    float m = -999;

    for(int i=0;i<5;i++){
        if (amplitude[i] > m) m = amplitude[i];
        coords.z += waveHeight(i, uv_in.x);
        vertNormal.x += waveDU(i, uv_in.x);
    }

    float a = smoothstep(-m,5*m,coords.z);
    materialColor = mix(vec3(0.25,0.5,1), vec3(0.8,0.8,0.8),a);
    vertNormal = normalize(vertNormal);

    vec4 position = (modelTransform * vec4(coords,1));
    gl_Position = perspectiveTransform * viewTransform * position;
    position_out = position.xyz;
}
