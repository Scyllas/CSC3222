#version 400 core

uniform float accumTime;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

layout(triangles) in;
layout(triangle_strip, max_vertices = 4) out;

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

void main() {
float particleSize= 10.0;
vec4 displaceFactor = vec4(10,10,1,10);
	for (int i = 0; i < gl_in.length(); ++i) {
		OUT.colour = IN[i].colour;
		// top right
		gl_Position = displaceFactor*gl_in[i].gl_Position;
		gl_Position.x += particleSize;
		gl_Position.y += particleSize;
		OUT.texCoord = vec2(1, 0);
		EmitVertex();
		// Then we do the other vertices of the quad ...
		// Top Left
		gl_Position = displaceFactor*gl_in[i].gl_Position;
		gl_Position.x -= particleSize;
		gl_Position.y += particleSize;
		OUT.texCoord = vec2(0, 0);
		EmitVertex();
		// bottom right
		gl_Position = displaceFactor*gl_in[i].gl_Position;
		gl_Position.x += particleSize;
		gl_Position.y -= particleSize;
		OUT.texCoord = vec2(1, 1);
		EmitVertex();
		// bottom Left
		gl_Position = displaceFactor*gl_in[i].gl_Position;
		gl_Position.x -= particleSize;
		gl_Position.y -= particleSize;
		OUT.texCoord = vec2(0, 1);
		EmitVertex();

		EndPrimitive();
	}
}