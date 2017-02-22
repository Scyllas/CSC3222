#include "Renderer.h"
#include "RenderObject.h"

#pragma comment(lib, "nclgl.lib")


void main(void) {
	int dimensions = 800;
	Window w = Window(dimensions, dimensions);
	Renderer r(w);

	Mesh*	m = Mesh::GenerateQuadPatch();

	
	Shader* s = new Shader("BasicVert.glsl", "BasicFrag.glsl", "BasicGeo.glsl");

	if (s->UsingDefaultShader()) {
		cout << "Warning: Using default shader! Your shader probably hasn't worked..." << endl;
		cout << "Press any key to continue." << endl;
		std::cin.get();
	}

	cout << s->GetShaderProgram() << endl;

	RenderObject o(m, s);
	
	SOIL_load_OGL_texture("cw_map.bmp", SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y);
	
	//o.SetModelMatrix(Matrix4::Translation(Vector3(0, 0, -10)) * Matrix4::Scale(Vector3(1, 1, 1)));

	float msec = w.GetTimer()->GetTimedMS();
	float rot;
	r.AddRenderObject(o);

	r.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.f, 45.0f));

	r.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10)));

	float accumTime = 1.f;
	while (w.UpdateWindow()) {

		msec = w.GetTimer()->GetTimedMS();
		accumTime += msec;

		
		
		o.SetModelMatrix(
			Matrix4::Translation(Vector3(0, 0, -10)) *
			Matrix4::Scale(Vector3(1, 1, 1))
		);



		r.UpdateScene(msec);
		r.ClearBuffers();
		r.RenderScene();
		r.SwapBuffers();
		//throttle fps
		Sleep(20);
	}
	delete m;
	delete s;
}

