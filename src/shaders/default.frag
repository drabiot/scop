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
	vec3 lightVec = lightPos - crntPos;
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	//Ambient Lighting
	float ambient = 0.20f;

	//Diffuse Lighting
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightVec);
	float diffuse = max(dot(norm, lightDir), 0.0f);

	//Specular Lighting
	float specLight = 0.50f;
	vec3 viewDir = normalize(camPos - crntPos);
	vec3 reflectionDir = reflect(-lightDir, norm);
	float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 8);
	float specular = specAmount * specLight;

	vec4 col = vec4(abs(color), 1.0);
    vec4 texture = texture(tex, texCoord);
    FragColor = (mix(col, texture, mixFactor) * (diffuse * inten + ambient + specular) * lightColor);
}
