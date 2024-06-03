#version 450

layout (location = 0) in vec3 aPos; //Set location 0 to pos from program.
layout (location = 1) in vec3 aColor; //Set location 1 to color from program.
layout (location = 2) in vec2 aTexCoord; //Texture coordinate.

uniform mat4 transform; 

out vec3 color;
out vec2 texCoord;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    color = aColor;
	texCoord = aTexCoord;
}