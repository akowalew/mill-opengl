#version 330 core

layout(location = 0) in vec3 position;

out vec3 toLightVector;

uniform vec3 lightPos;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 trans;

void main()
{
	vec4 worldPos = (trans * vec4(position, 1.0));
	gl_Position = (proj * view * worldPos);

	toLightVector = (lightPos - worldPos.xyz);
}
