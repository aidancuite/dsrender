#version 450

layout (location = 0) in vec3 aPos; //Set location 0 to pos from program.
layout (location = 1) in vec3 aColor; //Set location 1 to color from program.

out vec3 color;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    color = aColor;
}