#version 400 core

uniform float accumTime;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in Vertex {
vec3 position;
	vec2 texCoord;
	vec4 colour;
	vec4 worldPos;
} IN[];

out Vertex {
	vec3 position;
	vec2 texCoord;
	vec4 colour;	
	vec4 worldPos;
} OUT;

out vec4 FragColor;

void main () {


	for(int i = 0; i < gl_in.length(); ++i){
		gl_Position = gl_in[i].gl_Position;

		OUT.colour = IN[i].colour;
		OUT.texCoord = IN[i].texCoord;
		EmitVertex();
	}

	EndPrimitive();
}