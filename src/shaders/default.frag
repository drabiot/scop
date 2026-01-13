#version 330 core
out vec4 FragColor;

in vec3  color;
in vec3  texCoord;

in vec3 normal;
in vec3 crntPos;
in vec4 fragPosLight;

uniform sampler2DArray tex;
uniform float mixFactor;
uniform sampler2D uShadow;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	//Ambient Lighting
	float ambient = 0.20f;

	//Diffuse Lighting
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(norm, lightDir), 0.0f);

	//Specular Lighting
	float specLight = 0.50f;
	vec3 viewDir = normalize(camPos - crntPos);
	vec3 reflectionDir = reflect(-lightDir, norm);
	float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 8);
	float specular = specAmount * specLight;

	//Shadows
	float shadow = 0.0f;
    vec3 lightCoords = fragPosLight.xyz / fragPosLight.w;
    float closestDepth;
    float currentDepth;
    vec3 lightDirection = normalize(lightPos);
    lightCoords = (lightCoords + 1.0f) / 2.0f;
    currentDepth = lightCoords.z;

    float bias = max(0.005 * (1.0f - dot(normal, lightDirection)), 0.0005f);

	int sampleRadius = 2;
	vec2 pixelSize = 1.0 / textureSize(uShadow, 0);
	for (int y = -sampleRadius; y <= sampleRadius; y++) {
		for (int x = -sampleRadius; x <= sampleRadius; x++) {
			float closestDepth = texture(uShadow, lightCoords.xy + vec2(x, y) * pixelSize).r;
			if (currentDepth > closestDepth + bias)
				shadow += 1.0f;
		}
    }
	shadow /= pow((sampleRadius * 2 + 1), 2);

	vec4 col = vec4(abs(color), 1.0);
    vec4 texture = texture(tex, texCoord);
    FragColor = (mix(col, texture, mixFactor) * ((diffuse * (1.0f - shadow)) + ambient + specular) * lightColor);
}
