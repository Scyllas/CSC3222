#version 150 core
uniform sampler2D diffuseTex;
uniform sampler2D	staticTex;
uniform sampler2D	perlinTex;
uniform sampler2D	smileyTex;
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
out vec4 FragColor;

void main ( void ) {
	vec4 tex1 = texture ( staticTex , IN.texCoord*sin(accumTime*0.0001));
	vec4 tex2 = texture ( perlinTex , IN.texCoord*cos(accumTime*0.001));
	vec4 tex3 = texture ( smileyTex , IN.texCoord*4*cos(accumTime*0.001));

	if(tex3.b > 0.1) {
		FragColor+=tex3;
	}else{
		FragColor = tex1*tex2;
	}
}