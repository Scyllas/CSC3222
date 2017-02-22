#version 400 core

layout(triangles, equal_spacing, ccw) in;
uniform sampler2D diffuseTex;
uniform sampler2D	smileyTex;
uniform sampler2D	staticTex;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform float accumTime;

in Vertex{
	vec3 position;
	vec2 texCoord;
	smooth vec4 colour;
	smooth vec4 worldPos;
} IN[];
out Vertex{
	vec3 position;
	vec2 texCoord;
	smooth vec4 colour;
	smooth vec4 worldPos;
} OUT;

void main() {
	vec3 p0 = gl_TessCoord.x * gl_in[0].gl_Position.xyz;
	vec3 p1 = gl_TessCoord.y * gl_in[1].gl_Position.xyz;
	vec3 p2 = gl_TessCoord.z * gl_in[2].gl_Position.xyz;

	vec3 combinedPos = p0 + p1 + p2;

	vec4 worldPos = modelMatrix * vec4(combinedPos, 1);


	gl_Position = projMatrix * viewMatrix * worldPos;
}
