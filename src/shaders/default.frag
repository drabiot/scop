#version 330 core
out vec4 FragColor;

in vec3  color;
in vec3  texCoord;

in vec3 normal;
in vec3 crntPos;

uniform sampler2DArray tex;
uniform float mixFactor;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	float ambient = 0.20f;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - crntPos);
	float diffuse = max(dot(norm, lightDir), 0.0f);

	float specLight = 0.50f;
	vec3 viewDir = normalize(camPos - crntPos);
	vec3 reflectionDir = reflect(-lightDir, norm);
	float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 8);
	float specular = specAmount * specLight;

    vec4 col = vec4(abs(color), 1.0);
    vec4 texture = texture(tex, texCoord);
    FragColor = mix(col, texture, mixFactor) * lightColor * (diffuse + ambient + specular);
}
