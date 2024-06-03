#version 450

in vec3 color;
in vec2 texCoord;

out vec4 FragColor;

//Textures come into fragment shader, not vertex shader.
uniform sampler2D texture0; //Box
uniform sampler2D texture1; //Stew

uniform float sel;

void main()
{
	// FragColor = texture(texture1, texCoord) * vec4(color, 1.0);
	// vec2 dog = vec2(-texCoord.x, texCoord.y);
	FragColor = mix(texture(texture0, texCoord), texture(texture1, texCoord), sel) * vec4(color, 1.0f);
}