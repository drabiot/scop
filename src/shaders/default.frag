#version 330 core
out vec4 FragColor;

in vec3  color;
in vec3  texCoord;

uniform sampler2DArray tex;
uniform float mixFactor;

uniform vec4 lightColor;

void main()
{
    vec4 col = vec4(abs(color), 1.0);
    vec4 texture = texture(tex, texCoord);
    FragColor = mix(col, texture, mixFactor) * lightColor;
}
