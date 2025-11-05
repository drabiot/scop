#version 330 core
out vec4 FragColor;

in vec3  color;
in vec2  texCoord;

uniform sampler2D tex0;
uniform float mixFactor; // 0.0 = couleur, 1.0 = texture

void main()
{
    vec4 col = vec4(abs(color), 1.0);
    vec4 tex = texture(tex0, texCoord);
    FragColor = mix(col, tex, mixFactor);
}
