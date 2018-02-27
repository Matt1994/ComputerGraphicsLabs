#version 330 core

// Define constants
#define M_PI 3.141593

// Input
in vec3 vertColor;

// Output
out vec4 fColor;

void main()
{
    fColor = vec4(vertColor, 1.0);
}
