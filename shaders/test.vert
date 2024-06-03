#version 450

layout (location = 0) in vec3 aPos; //Set location 0 to pos from program.
layout (location = 1) in vec3 aColor; //Set location 1 to color from program.
layout (location = 2) in vec2 aTexCoord; //Texture coordinate.

uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 color;
out vec2 texCoord;

void main()
{
    gl_Position = projection * view * model *  transform * vec4(aPos, 1.0);
	// gl_Position = projection * view * model * vec4(aPos, 1.0);
    color = aColor;
	texCoord = aTexCoord;
}