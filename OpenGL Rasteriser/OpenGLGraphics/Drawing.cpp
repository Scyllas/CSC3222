#include "Drawing.h"


RenderObject Drawing::drawMap(Mesh* m, Renderer &r, Shader* s) {

	if (s->UsingDefaultShader()) {
		cout << "Warning: Using default shader! Your shader probably hasn't worked..." << endl;
		cout << "Press any key to continue." << endl;
		std::cin.get();
	}
	GLuint texture = r.LoadTexture("Images/cw_map.bmp", NULL);

	RenderObject map = RenderObject(m, s, texture);

	map.SetModelMatrix(Matrix4::Translation(Vector3(0.f, 0.f, 0.f)) * Matrix4::Scale(Vector3(1.f, 1.f, 1.f)));

	return map;
}

Entity* Drawing::drawSoldier(Mesh* m, Renderer &r, Shader* s) {

	if (s->UsingDefaultShader()) {
		cout << "Warning: Using default shader! Your shader probably hasn't worked..." << endl;
		cout << "Press any key to continue." << endl;
		std::cin.get();
	}
	GLuint texture = r.LoadTexture("Images/Soldier.bmp", NULL);

	float x = (rand() % 20 + 75)* 0.01f;
	float y = (rand() % 20 + 75)* 0.01f;
	float sf = 0.025f;
	
	Entity* soldier = new Entity(x, y, 0.f, 0.f, 1.f, sf, m, s, texture);
	soldier->setIsCommander(false);

	soldier->SetModelMatrix(Matrix4::Translation(Vector3(x, y, 0.f)) * Matrix4::Scale(Vector3(sf, sf, sf)));

	return soldier;
}

Entity Drawing::drawCommander(Mesh* m, Renderer &r, Shader* s) {


	if (s->UsingDefaultShader()) {
		cout << "Warning: Using default shader! Your shader probably hasn't worked..." << endl;
		cout << "Press any key to continue." << endl;
		std::cin.get();
	}
	GLuint texture = r.LoadTexture("Images/Commander.bmp", NULL);

	float x = 0.85f;
	float y = 0.85f;
	float sf = 0.025f;

	Entity commander = Entity(x, y, 0.f, 0.f, 5.f, sf, m, s, texture);
	commander.setIsCommander(true);

	commander.SetModelMatrix(Matrix4::Translation(Vector3(x, y, 0.f)) * Matrix4::Scale(Vector3(sf, sf, sf)));

	return commander;
}
