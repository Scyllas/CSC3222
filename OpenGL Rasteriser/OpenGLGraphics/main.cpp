#include "Drawing.h"
#include "GenerateTiles.h"
#include "Movement.h"
#include <time.h>

#pragma comment(lib, "nclgl.lib")



int* getCells(Entity* commander, Tile* tile, float rad) {

	Vector3 commanderPos = (commander->GetModelMatrix().GetPositionVector() * 10) + Vector3(10, 10, 0);
	float commandX = commanderPos.x;
	float commandY = commanderPos.y;
	rad = rad * 20;
	float rad45 = rad* cos45;

	Vector3 t(commandX, commandY + rad, 0);
	Vector3 b(commandX, commandY - rad, 0);

	Vector3 l(commandX - rad, commandY, 0);
	Vector3 r(commandX + rad, commandY, 0);

	Vector3 tl(commandX - rad45, commandY + rad45, 0);
	Vector3 tr(commandX + rad45, commandY + rad45, 0);

	Vector3 bl(commandX - rad45, commandY - rad45, 0);
	Vector3 br(commandX + rad45, commandY - rad45, 0);

	int* tiles = new int[SIZE_OF_ARRAYPOINTS];

	tiles[0] = (20 * (int)t.y) + (int)t.x;
	tiles[1] = (20 * (int)b.y) + (int)b.x;

	tiles[2] = (20 * (int)l.y) + (int)l.x;
	tiles[3] = (20 * (int)r.y) + (int)r.x;
	
	tiles[4] = (20 * (int)tl.y) + (int)tl.x;
	tiles[5] = (20 * (int)tr.y) + (int)tr.x;

	tiles[6] = (20 * (int)bl.y) + (int)bl.x;
	tiles[7] = (20 * (int)br.y) + (int)br.x;

	/*cout <<
		rad << ", " <<
		tiles[0] << ", " <<
		tiles[1] << ", " <<
		tiles[2] << ", " <<
		tiles[3] << ", " <<
		tiles[4] << ", " <<
		tiles[5] << ", " <<
		tiles[6] << ", " <<
		tiles[7] << endl;*/
	return tiles;
}

void squareToSquare(Tile* tiles, Movement move, Entity* s1, Entity* s2) {


	// collision calculation sourced from
	// https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection

	float s1x = s1->getX();
	float s1y = s1->getY();
	float s2y = s2->getY();
	float s2x = s2->getX();
	float s1rad = s1->getD() * 0.5f *  SCALE_FACTOR;
	float s2rad = s2->getD() * 0.5f *  SCALE_FACTOR;
	
	if (
		s1x < s2x + s2rad &&
		s1x + s1rad > s2x &&
		s1y < s2y + s2rad &&
		s1rad + s1y > s2y) {

		//return true;
		move.collisionResolution(s1, getCells(s1, tiles, s1rad), s2, getCells(s2, tiles, s2rad));
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

	srand(time(NULL));

	int dimensions = 1000;
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

	float rad = commander.getD() / 2.f;

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

		//	collisionDetection(tile, move, &commander, soldier);

		move.sceneControls(&commander, getCells(&commander, tile, rad), tile, rad);

		r.UpdateScene(msec);
		r.ClearBuffers();
		r.RenderScene();
		r.SwapBuffers();

	}
	delete s;
	delete m;


}

