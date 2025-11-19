#version 330 core
out vec4 FragColor;

in vec3  color;
in vec3  texCoord;

uniform sampler2DArray tex;
uniform float mixFactor;

void main()
{
    vec4 col = vec4(abs(color), 1.0);
    vec4 texture = texture(tex, texCoord);
    FragColor = mix(col, texture, mixFactor);
}
