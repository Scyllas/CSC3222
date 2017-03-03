#include "Movement.h"


Movement::Movement()
{
	grassPlains = Vector3(214, 254, 139);
	field = Vector3(103, 220, 69);
	forest = Vector3(34, 177, 76);
	bridge = Vector3(96, 60, 40);
	goal = Vector3(185, 122, 87);
	wall = Vector3(127, 127, 127);
	castle = Vector3(195, 195, 195);
	start = Vector3(239, 228, 176);
	water = Vector3(153, 217, 234);
}


float Movement::sceneControls(Entity* r, Tile t) {

	Vector3 colour = Vector3(t.getRGB());
	float damping;
	//cout << t.getCoordinate() << ", " << t.getRGB() << endl;
	if (colour == grassPlains) 		damping = 1.0f;

	else if (colour == field)		damping = 1.0f;

	else if (colour == forest)		damping = 0.5f;

	else if (colour == bridge)		damping = 1.0f;

	else if (colour == goal) 		damping = 0.15f;

	else if (colour == castle)		damping = 1.0f;

	else if (colour == start) 		damping = 1.0f;

	else if (colour == water) 		damping = 0.35f;

	else if (colour == wall) {
		damping = -0.9f;
/*
		for (int i = 0; i < 50;) {
			cout << r->getPrevPos(i) << endl;
		}
			r->setPosition(r->getPrevPos(49));*/
	}

	else {
		damping = 0.f;
		cout << "Error reading tile" << endl;
	}
	if (r->getIsCommander() == true) {
		move(r, damping);
	}
	return damping;
}

void Movement::move(Entity* r, float damping) {

	Matrix4 temp = r->GetModelMatrix();
	//cout << r->GetModelMatrix().GetPositionVector() << endl;
	Vector3 a = Vector3(0, 0, 0);
	Vector3 u = r->getPrevVelocity() * damping;
	float t = 0.01f;
	//	cout << u << endl;
	if (u.x < 0.0001f && u.x > -0.0001f) { u.x = 0; }
	if (u.y < 0.0001f && u.y > -0.0001f) { u.y = 0; }

	if (Keyboard::KeyDown(KEY_A)) {
		a = Vector3(-0.1f, 0.f, 0.f);
		r->setPosition(r->GetModelMatrix().GetPositionVector());
		r->setPrevVelocity(s.V_is_UAT(u, a, t));
		r->SetModelMatrix(temp * Matrix4::Translation((s.V_is_UAT(u, a, t))));
	}
	else if (Keyboard::KeyDown(KEY_D)) {
		a = Vector3(0.1f, 0.f, 0.f);
		r->setPosition(r->GetModelMatrix().GetPositionVector());
		r->setPrevVelocity(s.V_is_UAT(u, a, t));
		r->SetModelMatrix(temp * Matrix4::Translation((s.V_is_UAT(u, a, t))));
	}
	else if (Keyboard::KeyDown(KEY_W)) {
		a = Vector3(0.f, 0.1f, 0.f);
		r->setPosition(r->GetModelMatrix().GetPositionVector());
		r->setPrevVelocity(s.V_is_UAT(u, a, t));
		r->SetModelMatrix(temp * Matrix4::Translation((s.V_is_UAT(u, a, t))));

	}
	else if (Keyboard::KeyDown(KEY_S)) {
		a = Vector3(0.f, -0.1f, 0.f);
		r->setPosition(r->GetModelMatrix().GetPositionVector());
		r->setPrevVelocity(s.V_is_UAT(u, a, t));
		r->SetModelMatrix(temp * Matrix4::Translation((s.V_is_UAT(u, a, t))));
	}
	else {
		a = Vector3(0.f, 0.f, 0.f);
		r->setPosition(r->GetModelMatrix().GetPositionVector());
		r->setPrevVelocity(s.V_is_UAT(u, a, t));
		r->SetModelMatrix(temp * Matrix4::Translation((s.V_is_UAT(u, a, t))));
	}


}

void Movement::collisionResolution(Entity* s1, Tile t1, Entity* s2, Tile t2) {

	Vector3 s1Pos = s1->getPosition();
	Vector3 s2Pos = s2->getPosition();

	float m = (s2Pos.y - s1Pos.y) / (s2Pos.x - s1Pos.x);

	//angle from the x axis
	float angle = atan(m);
	float s1theta;
	float s2theta;
	if (angle >= 0) {
		s1theta = M_PI * 0.5 - angle;
		s2theta = M_PI * 2 - angle;
	}
	else {
		s1theta = M_PI * 0.5 + angle;
		s2theta = M_PI * 2 + angle;
	}
	//-------------|------------|-----------|------------|-----------
	//-------------|------------|-----------|------------|-----------
	//------------s1_-----------|-----------|----------_s2-----------
	//-------------|--_---------|-----------|--------_---|-----------
	//-------------|----_-------|-----------|------_-----|-----------
	//-------------|------_-----|-----------|----_-------|-----------
	//-------------|--------_---|-----------|--_---------|-----------
	//-------------|----------_-|-----------|_-----------|-----------
	//-------------|-----------s2----------s1------------|-----------

	Matrix4 s1temp = s1->GetModelMatrix();
	Vector3 s1u = s1->getPrevVelocity() * sceneControls(s1, t1);
	Vector3 s1a = Vector3(1 * sin(s1theta), 1 * sin(s1theta), 0) * 0.01f;
	Vector3 s2u = s2->getPrevVelocity() * sceneControls(s2, t2);
	Vector3 s2a = Vector3(1 * sin(s2theta), 1 * sin(s2theta), 0) * 0.01f;
	float t = 0.01f;

	//	s1->setPrevVelocity(s.V_is_UAT(s1u, s1a, 1));
	//	s1->SetModelMatrix(s1temp * Matrix4::Translation((s.V_is_UAT(s1u, s1a / s1->getMass(), t))));
	//	s2->setPrevVelocity(s.V_is_UAT(s2u, s2a, 1));
	//	s2->SetModelMatrix(s1temp * Matrix4::Translation((s.V_is_UAT(s1u, s1a / s1->getMass(), t))));
}

Movement::~Movement()
{
}
