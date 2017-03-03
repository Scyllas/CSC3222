#include "Drawing.h"
#include "GenerateTiles.h"
#include "Movement.h"

#pragma comment(lib, "nclgl.lib")

Tile getCell(Entity* commander, Tile* tile) {

	Vector3 coord = (commander->GetModelMatrix().GetPositionVector() * 10) + Vector3(10, 10, 0);

	return tile[(20 * (int)coord.y) + (int)coord.x];
}

void squareToSquare(Tile* tiles, Movement move, Entity* s1, Entity* s2) {


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
		move.collisionResolution(s1, getCell(s1, tiles), s2, getCell(s2, tiles));
	}

}

void collisionDetection(Tile* tiles, Movement move, Entity* commander, vector<Entity*>& soldier) {

	for (unsigned int i = 0; i < soldier.size(); i++) {
		squareToSquare(tiles, move, commander, soldier[i]);
	}

	for (unsigned int i = 0; i < soldier.size(); i++) {
		for (unsigned int j = i + 1; j < soldier.size(); j++) {
			squareToSquare(tiles, move, soldier[i], soldier[j]);
		}
	}
}


void cam(Renderer& r) {


	r.SetProjectionMatrix(Matrix4::Orthographic(1.f, -1.f, 1.f, -1.f, 1.f, -1.f));
	//r.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.f, 45.0f));
	r.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -1.f)));
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
	Movement move;
	Tile* tile = g.getTiles();
	Entity commander = d.drawCommander(m, r, s);
	vector<Entity*> soldier = vector<Entity*>();
	RenderObject map = d.drawMap(m, r, s);
	commander.setIsCommander(true);

	r.AddRenderObject(commander);

	for (int i = 0; i < soldierNum; i++) {
		soldier.push_back(d.drawSoldier(m, r, s));
		r.AddRenderObject(*soldier[i]);
	}
	r.AddRenderObject(map);



	char* string = "hello";

	//cout << s->GetShaderProgram() << endl;

	float msec = w.GetTimer()->GetTimedMS();
	float accumTime = 1.f;

	while (w.UpdateWindow()) {

		msec = w.GetTimer()->GetTimedMS();

		//collisionDetection(tile, move, &commander, soldier);

		move.sceneControls(&commander, getCell(&commander, tile));

		r.UpdateScene(msec);
		r.ClearBuffers();
		r.RenderScene();
		r.SwapBuffers();

	}
	delete s;
	delete m;


}

