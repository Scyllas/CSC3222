#version 150 core

uniform sampler2D	smileyTex;
uniform sampler2D	staticTex;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform float accumTime;

in Vertex	{
	vec3 position;
	smooth vec2 texCoord;
	smooth vec4 colour;
	smooth vec4 worldPos;
} IN;

//In the tutorial notes, I've used gl_FragColor for the output variable. This is fine on the uni machines, but 
//doesn't play very nicely with some intel and amd graphics drivers, due to the gl_ prefix. For this reason,
//it's better to use a different variable name - so pick something sensible.


out vec4 fragColour;

void main(void)	{	
//vec4 worldPos = modelMatrix * vec4(IN.position , 1.0);
float r = sin(accumTime/1000);
float g = cos(accumTime/1000) + 3.14/4;
float b = 0.5;
fragColour = vec4(r,g,b,1);
}