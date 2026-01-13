#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTex;
layout (location = 2) in vec3 aNormal;

out vec3 color;
out vec3 texCoord;

out vec3 normal;
out vec3 crntPos;
out vec4 fragPosLight;

uniform mat4	camMatrix;
uniform mat4	model;
uniform mat4	lightProjection;

void main()
{
	crntPos = vec3(model * vec4(aPos, 1.0f));

	gl_Position = camMatrix * vec4(crntPos, 1.0);
	color = aNormal;
	texCoord = aTex;

    fragPosLight = lightProjection * vec4(vec3(model * vec4(aPos, 1.0f)), 1.0f);

	//normal = aNormal;
	normal = mat3(transpose(inverse(model))) * aNormal;
}