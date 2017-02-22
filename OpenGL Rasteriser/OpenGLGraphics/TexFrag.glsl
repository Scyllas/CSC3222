#version 150 core
uniform sampler2D diffuseTex;
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
vec4 smileyColour = texture(smileyTex, IN.texCoord);

	if(smileyColour.b > 0.1) {
		vec2 tempTex = IN.texCoord;
		tempTex.y += accumTime;

		fragColour = texture(staticTex, tempTex);
	}
	else{
	fragColour = smileyColour;
	}
}