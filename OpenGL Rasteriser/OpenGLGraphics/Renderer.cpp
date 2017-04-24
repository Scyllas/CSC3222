#include "Renderer.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent) {

	glPatchParameteri(GL_PATCH_VERTICES, 3);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

}

Renderer::~Renderer(void) {

}

GLuint Renderer::LoadTexture(string filename, unsigned int flag) {

	return SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, flag);

}

void	Renderer::RenderScene() {
	ClearBuffers();
	for (vector<RenderObject*>::iterator i = renderObjects.begin(); i != renderObjects.end(); ++i) {
		Render(*(*i));
	}
}

void	Renderer::Render(const RenderObject &o) {
	
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

		glActiveTexture(GL_TEXTURE0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, o.GetTexture());


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