#version 400 core

layout(vertices = 3) out;

uniform sampler2D	smileyTex;
uniform sampler2D	staticTex;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform float accumTime;
uniform float tessLevelInner;
uniform float tessLevelOuter;

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
} OUT[];

out vec4 FragColor[];


void main() {
	gl_TessLevelInner[0] = tessLevelInner;

	gl_TessLevelOuter[0] = tessLevelOuter;
	gl_TessLevelOuter[1] = tessLevelOuter;
	gl_TessLevelOuter[2] = tessLevelOuter;

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}