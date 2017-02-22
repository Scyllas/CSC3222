#version 400 core

layout(vertices=4)out; // num vertices in patch output

uniform sampler2D heightMap;

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

//out vec4 FragColor[];

 void main () {
 gl_TessLevelInner [0] = 16;
 gl_TessLevelInner [1] = 16;
 gl_TessLevelOuter [0] = 16;
 gl_TessLevelOuter [1] = 16;
 gl_TessLevelOuter [2] = 16;
 gl_TessLevelOuter [3] = 16;

 OUT [gl_InvocationID].texCoord = IN[gl_InvocationID].texCoord ;

 gl_out[gl_InvocationID].gl_Position =
 gl_in[gl_InvocationID].gl_Position;
 }