#version 330 core
out vec4 FragColor;

in vec3				color;
in vec2				texCoord;

uniform sampler2D	tex0;
uniform bool		display;

void main()
{
	if (!display)
		FragColor = vec4(abs(color), 1.0);
	else
		FragColor = texture(tex0, texCoord);
}
