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
	vec4 worldPos	=  modelMatrix * vec4 ( position , 1.0);
	float mod = sin(accumTime/1000);
	worldPos.y += mod;
	gl_Position = projMatrix * viewMatrix * worldPos;
	OUT.texCoord	= texCoord;
	OUT.colour		= colour;
	
}