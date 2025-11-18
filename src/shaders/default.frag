#version 330 core
out vec4 FragColor;

in vec3  color;
in vec3  texCoord;

uniform sampler2DArray tex0;
uniform float mixFactor;

void main()
{
    vec4 col = vec4(abs(color), 1.0);
    vec4 tex = texture(tex0, texCoord);
    FragColor = mix(col, tex, mixFactor);
}
