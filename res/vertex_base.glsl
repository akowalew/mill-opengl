#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 toLightVector;
out vec3 surfaceNormal;

uniform vec3 lightPos;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 trans;

void main()
{
	vec4 worldPos = (trans * vec4(position, 1.0));
	gl_Position = (proj * view * worldPos);

	surfaceNormal = (trans * vec4(normal, 0.0)).xyz;
	toLightVector = (lightPos - worldPos.xyz);
}
