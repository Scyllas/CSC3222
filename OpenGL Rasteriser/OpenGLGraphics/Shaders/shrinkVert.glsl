#version 330 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform float accumTime;
uniform mat4 matrices[3];

layout ( location = 0) in vec3 position;
layout ( location = 1) in vec4 colour;
layout ( location = 2) in vec2 texCoord;

out Vertex	{
	vec3 position;
	vec2 texCoord;
	vec4 colour;
	vec4 worldPos;
} OUT;


void main(void)	{
	gl_Position		= (projMatrix * viewMatrix * modelMatrix) *vec4 (position , 1.0);
	OUT.texCoord	= texCoord;
	OUT.colour		= colour;
	OUT.colour.r	= sin(accumTime/2000.0f);
}