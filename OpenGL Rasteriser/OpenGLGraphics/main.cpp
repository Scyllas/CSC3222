#include "Drawing.h"
#include "GenerateTiles.h"

#pragma comment(lib, "nclgl.lib")

struct Cells {
	Vector3
		forest,
		field,
		grass,
		water,
		bridge,
		goal,
		start,
		castle,
		wall;

};

void squareToSquare(Entity* s1, Entity* s2) {


	// collision calculation sourced from
	// https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection

	float s1x = s1->getX();
	float s1y = s1->getY();
	float s1w = s1->getD() * 2;
	float s2x = s2->getX();
	float s2y = s2->getY();
	float s2w = s2->getD() * 2;

	if (
		s1x < s2x + s2w &&
		s1x + s1w > s2x &&
		s1y < s2y + s2w &&
		s1w + s1y > s2y) {

		//return true;
		//perform collision resolution
	}

	else {

		//return false;

		//perform collision resolution
	}

}

void collisionDetection(Entity* commander, vector<Entity*>& soldier) {

	for (unsigned int i = 0; i < soldier.size(); i++) {
		squareToSquare(commander, soldier[i]);
	}

	for (unsigned int i = 0; i < soldier.size(); i++) {
		for (unsigned int j = i + 1; j < soldier.size(); j++) {
			squareToSquare(soldier[i], soldier[j]);
		}
	}
}

void sceneControls(RenderObject* r, Tile t) {



	Matrix4 temp = r->GetModelMatrix();

	if (Keyboard::KeyDown(KEY_A)) {
		r->SetModelMatrix(temp *
			Matrix4::Translation(Vector3(-0.1f, 0, 0)));

	}
	if (Keyboard::KeyDown(KEY_D)) {
		r->SetModelMatrix(temp *
			Matrix4::Translation(Vector3(0.1f, 0, 0)));

	}
	if (Keyboard::KeyDown(KEY_W)) {
		r->SetModelMatrix(temp *
			Matrix4::Translation(Vector3(0.0, 0.1f, 0)));

	}
	if (Keyboard::KeyDown(KEY_S)) {
		r->SetModelMatrix(temp *
			Matrix4::Translation(Vector3(0.0, -0.1f, 0)));
	}


}

void cam(Renderer& r) {


	r.SetProjectionMatrix(Matrix4::Orthographic(1.f, -1.f, 1.f, -1.f, 1.f, -1.f));
	//r.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.f, 45.0f));
	r.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -1.f)));
}


Tile getCell(Entity* commander, Tile* tile) {

	Vector3 coord = (commander->GetModelMatrix().GetPositionVector() * 10) + Vector3(10, 10, 0);

	return tile[(10 * (int)coord.y) + (int)coord.x];
}

void main(void) {
	int dimensions = 800;
	Window w = Window(dimensions, dimensions);
	Renderer r(w);

	int soldierNum = 4;

	Mesh*	m = Mesh::GenerateQuadPatch();
	Shader* s = new Shader("Shaders/BasicVert.glsl", "Shaders/BasicFrag.glsl");

	cam(r);
	Drawing d;
	GenerateTiles g;
	Tile* tile = g.getTiles();
	Entity commander = d.drawCommander(m, r, s);
	vector<Entity*> soldier = vector<Entity*>();
	RenderObject map = d.drawMap(m, r, s);


	r.AddRenderObject(commander);

	for (int i = 0; i < soldierNum; i++) {
		soldier.push_back(d.drawSoldier(m, r, s));
		r.AddRenderObject(*soldier[i]);
	}
	r.AddRenderObject(map);





	//cout << s->GetShaderProgram() << endl;

	float msec = w.GetTimer()->GetTimedMS();
	float accumTime = 1.f;

	while (w.UpdateWindow()) {

		msec = w.GetTimer()->GetTimedMS();

		collisionDetection(&commander, soldier);
		//no between -1 and 1




		sceneControls(&commander, getCell(&commander, tile));

		r.UpdateScene(msec);
		r.ClearBuffers();
		r.RenderScene();
		r.SwapBuffers();

	}
	delete s;
	delete m;


}

