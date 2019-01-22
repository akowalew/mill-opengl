#version 330 core

in vec3 surfaceNormal;
in vec3 toLightVector;

out vec4 outColor;

uniform vec3 color;
uniform vec3 lightColor;

void main()
{
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);

	float nDotl = dot(unitNormal, unitLightVector);
	float brightness = max(nDotl, 0.0);
	vec3 diffuse = (brightness * lightColor);

	outColor = vec4(diffuse * color, 1.0);
}
