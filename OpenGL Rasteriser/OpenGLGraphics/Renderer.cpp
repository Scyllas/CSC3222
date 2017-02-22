#include "Renderer.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent) {


	smileyTex = LoadTexture("smiley.png");
	staticTex = LoadTexture("noise.png");
	nyanTex = LoadTexture("nyancat.png");
	perlinTex = LoadTexture("perlin.png");
	Mesh * points = Mesh::GeneratePoints(100);

	glPatchParameteri(GL_PATCH_VERTICES, 3);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	if (Keyboard::KeyDown(KEY_SPACE)) {

	
	modelMatrix = Matrix4::Rotation(90, Vector3(1, 0, 0)) *
		Matrix4::Scale(Vector3(100, 100, 100));

	viewMatrix = Matrix4::Rotation(70.0f, Vector3(1, 0, 0)) *
		Matrix4::Rotation(-225.0f, Vector3(0, 1, 0)) *
		Matrix4::Translation(Vector3(100, -400, 100));

	projMatrix = Matrix4::Perspective(1.0f, 1000.0f,
		(float)width / (float)height, 45.0f);

	
	}
}

Renderer::~Renderer(void) {

}

GLuint Renderer::LoadTexture(string filename) {

	return SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

}

void	Renderer::RenderScene() {

	for (vector<RenderObject*>::iterator i = renderObjects.begin(); i != renderObjects.end(); ++i) {
		Render(*(*i));
	}
}

void	Renderer::Render(const RenderObject &o) {
	ClearBuffers();
	modelMatrix = o.GetWorldTransform();


	if (o.GetShader() && o.GetMesh()) {
		GLuint program = o.GetShader()->GetShaderProgram();
		GLint location = glGetUniformLocation(program, "modelMatrix");

		glUseProgram(program);

		UpdateShaderMatrices(program);

		glBindAttribLocation(program, 0, "position");
		glBindAttribLocation(program, 1, "colour");
		glBindAttribLocation(program, 2, "texCoord");

		glUniform1f(glGetUniformLocation(program, "accumTime"), accumTime);

		glUniform1i(glGetUniformLocation(program, "smileyTex"), 0);
		glUniform1i(glGetUniformLocation(program, "staticTex"), 1);
		glUniform1i(glGetUniformLocation(program, "nyanTex"), 2);
		glUniform1i(glGetUniformLocation(program, "diffuseTex"), 3);
		glUniform1i(glGetUniformLocation(program, "perlinTex"), 4);
	

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, smileyTex); 
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, staticTex); 
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, nyanTex); 
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, o.GetTexture());
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, perlinTex);


		o.Draw();
	}

	for (vector<RenderObject*>::const_iterator i = o.GetChildren().begin(); i != o.GetChildren().end(); ++i) {
		Render(*(*i));
	}
}

void	Renderer::UpdateScene(float msec) {

	accumTime += msec;

	for (vector<RenderObject*>::iterator i = renderObjects.begin(); i != renderObjects.end(); ++i) {
		(*i)->Update(msec);
	}
}