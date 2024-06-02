#version 450

in vec3 color;
in vec2 texCoord;

out vec4 FragColor;

//Textures come into fragment shader, not vertex shader.
uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	// FragColor = texture(texture1, texCoord) * vec4(color, 1.0);
	FragColor = mix(texture(texture0, texCoord), texture(texture1, texCoord), 0.2f);
}