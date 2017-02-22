#include "Renderer.h"
#include "RenderObject.h"

#pragma comment(lib, "nclgl.lib")


Matrix4 sceneControls(Matrix4 viewMatrix) {

	Vector3 camTranslate = Vector3(0, 0, -8);
	float speed = 0.01f;

	if (Keyboard::KeyDown(KEY_PLUS)) {
		viewMatrix = viewMatrix *
			Matrix4::Scale(Vector3(1.1, 1.1, 1.1));

	}
	if (Keyboard::KeyDown(KEY_MINUS)) {
		viewMatrix = viewMatrix *
			Matrix4::Scale(Vector3(0.9, 0.9, 0.9));

	}
	if (Mouse::ButtonDown(MOUSE_LEFT)) {
		float yawX = 0.0f;
		float yawY = 0.0f;
		yawX += Mouse::GetRelativePosition().x;
		viewMatrix = viewMatrix * Matrix4::Rotation(yawX, Vector3(0, 0.00001, 0));
		yawY += Mouse::GetRelativePosition().y;
		viewMatrix = viewMatrix * Matrix4::Rotation(yawY, Vector3(0.00001, 0, 0));
	}
	if (Keyboard::KeyTriggered(KEY_G)) {

		camTranslate.z += speed;

	}
	if (Keyboard::KeyTriggered(KEY_H)) {
		camTranslate.z -= speed;

	}
	if (Keyboard::KeyDown(KEY_A)) {
		viewMatrix = viewMatrix *
			Matrix4::Translation(Vector3(0.01f, 0, 0));

	}
	if (Keyboard::KeyDown(KEY_D)) {
		viewMatrix = viewMatrix *
			Matrix4::Translation(Vector3(-0.01f, 0, 0));

	}
	if (Keyboard::KeyDown(KEY_W)) {
		viewMatrix = viewMatrix *
			Matrix4::Translation(Vector3(0.0, -0.01f, 0));

	}
	if (Keyboard::KeyDown(KEY_S)) {
		viewMatrix = viewMatrix *
			Matrix4::Translation(Vector3(0.0, 0.01f, 0));
	}
	if (Keyboard::KeyDown(KEY_CONTROL)) {
		viewMatrix = viewMatrix *
			Matrix4::Translation(Vector3(0.0f, 0.0f, -0.01f));
	}
	if (Keyboard::KeyDown(KEY_SHIFT)) {
		viewMatrix = viewMatrix *
			Matrix4::Translation(Vector3(0.0, 0.0f, 0.01f));
	}

	return viewMatrix;
}

void cam(RenderObject& o, Renderer& r) {

	o.SetModelMatrix(Matrix4::Translation(Vector3(0, 0, 0)) * Matrix4::Scale(Vector3(1, 1, 1)));

	r.AddRenderObject(o);
	r.SetProjectionMatrix(Matrix4::Orthographic(0.5f, -0.5f, 0.5f, -0.5f, 0.5f, -0.5f));
	//r.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.f, 45.0f));
	r.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -0.5)));
}

RenderObject drawMap(Renderer &r, Shader* s) {

	Mesh* m = Mesh::GenerateQuadPatch();

	s = new Shader("Shaders/BasicVert.glsl", "Shaders/BasicFrag.glsl");

	if (s->UsingDefaultShader()) {
		cout << "Warning: Using default shader! Your shader probably hasn't worked..." << endl;
		cout << "Press any key to continue." << endl;
		std::cin.get();
	}
	GLuint texture = r.LoadTexture("Images/cw_map.bmp", NULL);

	return RenderObject(m, s, texture);
}


void main(void) {
	int dimensions = 800;
	Window w = Window(dimensions, dimensions);
	Renderer r(w);

	Mesh*	m = Mesh::GenerateQuadPatch();

	Shader* x = new Shader("Shaders/BasicVert.glsl", "Shaders/BasicFrag.glsl");

	if (x->UsingDefaultShader()) {
		cout << "Warning: Using default shader! Your shader probably hasn't worked..." << endl;
		cout << "Press any key to continue." << endl;
		std::cin.get();
	}
	GLuint texture = r.LoadTexture("Images/cw_map.bmp", NULL);
	RenderObject n(m, x, texture);

	r.AddRenderObject(n);

	r.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.f, 45.0f));

	r.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10)));
	
	Matrix4 viewMatrix = Matrix4::Translation(Vector3(0, 0, -10.0f));



	Shader* s = NULL;

	//RenderObject o = drawMap(r, s);


	/*
		int imageWidth = -1;
		int imageHeight = -1;
		int imageChannel = -1;
		int ImageChannelForce = SOIL_LOAD_AUTO;
		unsigned char* background = SOIL_load_image("cw_map.bmp",
			&imageWidth, &imageHeight, &imageChannel, ImageChannelForce);
	*/

	//cout << s->GetShaderProgram() << endl;


	//o.SetModelMatrix(Matrix4::Translation(Vector3(0, 0, -10)) * Matrix4::Scale(Vector3(1, 1, 1)));

	float msec = w.GetTimer()->GetTimedMS();
	float accumTime = 1.f;

	while (w.UpdateWindow()) {

		msec = w.GetTimer()->GetTimedMS();
		accumTime += msec;


		viewMatrix = sceneControls(viewMatrix);

		n.SetModelMatrix(
			Matrix4::Translation(Vector3(0, 0, -10)) *
		//	Matrix4::Rotation(0.1f * accumTime, Vector3(1, 0.8, 0.3))*
			Matrix4::Scale(Vector3(1, 1, 1))
		);

		r.SetViewMatrix(viewMatrix);
		r.UpdateScene(msec);
		r.ClearBuffers();
		r.RenderScene();
		r.SwapBuffers();

	}
	delete s;
}

