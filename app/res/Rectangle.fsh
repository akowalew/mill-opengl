#version 330 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D texIIPW;
uniform sampler2D texWEITI;

void main()
{
    outColor =
    	mix(texture(texIIPW, Texcoord), texture(texWEITI, Texcoord), 0.5)
    		* vec4(1 - Color, 1.0);
}
