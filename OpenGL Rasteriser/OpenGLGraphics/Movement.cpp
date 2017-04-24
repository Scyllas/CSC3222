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


void Movement::sceneControls(Entity* r, int* tileLoc, Tile* t, float rad) {




	r->setDamping(0.99f);
	float maxSpeed = 0.f;
	float y = r->getPosition().y;
	float x = r->getPosition().x;
	bool isWall = false;
	static int temp = 0;


	//cout << x << ", " << y << endl;

	for (int i = 0; i < SIZE_OF_ARRAYPOINTS; i++) {

		Vector3 colour = Vector3(t[tileLoc[i]].getRGB());

		if (colour == grassPlains) { maxSpeed += 1.f; /*cout << "grass";*/ }
		else if (colour == field) { maxSpeed += 1.0f; /*cout << "field";*/ }
		else if (colour == forest) { maxSpeed += 0.5f;/* cout << "forest";*/ }
		else if (colour == bridge) { maxSpeed += 1.0f; /*cout << "bridge";*/ }
		else if (colour == castle) { maxSpeed += 1.0f; /*cout << "castle";*/ }
		else if (colour == start) { maxSpeed += 1.0f; /*cout << "start";*/ }
		else if (colour == water) { maxSpeed += 0.35f; /*cout << "water";*/ }
		else if (colour == wall) {

			isWall = true;
			/*
						if (x > 0.70f) {
							r->SetModelMatrix(r->GetModelMatrix() * Matrix4::Translation(Vector3(0.2f, 0.f, 0.f)));
						}
						else if (x < -0.70f) {
							r->SetModelMatrix(r->GetModelMatrix() * Matrix4::Translation(Vector3(-0.2f, 0.f, 0.f)));
						}
						else if (y < -0.80f && y > -0.90f && x > -0.70f && x < 0.70f) {
							r->SetModelMatrix(r->GetModelMatrix() * Matrix4::Translation(Vector3(0.f, 0.2f, 0.f)));
						}*/
		}
		else if (colour == goal) {
			maxSpeed = 0.15f;
			//end AI

		}
		else {
			r->setDamping(-0.9f);
			cout << "Error reading tile" << endl;
		}

		/*cout << endl;*/
		if (x + rad > 1.f) {
			r->SetModelMatrix(r->GetModelMatrix() * 
				Matrix4::Rotation(r->currentRotation * 1.f, Vector3(0.f, 0.f, 1.f))* 
				Matrix4::Translation(Vector3(-rad,0.f,  0.f))* 
				Matrix4::Rotation(r->currentRotation * -1.f, Vector3(0.f, 0.f, 1.f)));

		}
		if (x - rad < -1.f) {
			r->SetModelMatrix(r->GetModelMatrix() *
				Matrix4::Rotation(r->currentRotation * 1.f, Vector3(0.f, 0.f, 1.f))*
				Matrix4::Translation(Vector3(rad,0.f,  0.f))*
				Matrix4::Rotation(r->currentRotation * -1.f, Vector3(0.f, 0.f, 1.f)));
		}
		if (y + rad > 1.f) {

			r->SetModelMatrix(r->GetModelMatrix() *
				Matrix4::Rotation(r->currentRotation * 1.f, Vector3(0.f, 0.f, 1.f))*
				Matrix4::Translation(Vector3(0.f, -rad, 0.f))*
				Matrix4::Rotation(r->currentRotation * -1.f, Vector3(0.f, 0.f, 1.f)));
		}
		if (y - rad < -1.f) {
			r->SetModelMatrix(r->GetModelMatrix() *
				Matrix4::Rotation(r->currentRotation * 1.f, Vector3(0.f, 0.f, 1.f))*
				Matrix4::Translation(Vector3(0.f, rad, 0.f))*
				Matrix4::Rotation(r->currentRotation * -1.f, Vector3(0.f, 0.f, 1.f)));
		}
		//cout << maxSpeed << endl;
		r->setMaxSpeed(maxSpeed * SCALE_OVER_ARRAYSIZE);

		if (r->getIsCommander() == true) {
			move(r, isWall);
		}
	}
}

void Movement::move(Entity* r, bool isWall) {

	//cout << r->GetModelMatrix().GetPositionVector() << endl;
	Vector3 a = Vector3(0.f, 0.f, 0.f);

	float t = 0.01f;
	//	cout << u << endl;

	r->currentRotation = 0;
	//left
	if (Keyboard::KeyDown(KEY_A)) {
		r->currentRotation = 0.1f;
	}
	//right
	else if (Keyboard::KeyDown(KEY_D)) {
		r->currentRotation = -0.1f;
	}
	//up
	if (Keyboard::KeyDown(KEY_W)) {
		if (r->getMaxSpeed() > abs(r->getPrevVelocity().y)) {
			a = a + Vector3(0.f, 0.1f, 0.f);
		}
		else {
			r->setDamping(0.9f);
		}
	}

	if (isWall) {
		a = Vector3(0.f, 0.f, 0.f);
	}

	Vector3 u = r->getPrevVelocity() * r->getDamping();

	if (u.x < 0.0001f && u.x > -0.0001f) u.x = 0;
	if (u.y < 0.0001f && u.y > -0.0001f) u.y = 0;


	r->setPosition(r->GetModelMatrix().GetPositionVector());
	r->setPrevVelocity(s.V_is_UAT(u, a, t));
	r->SetModelMatrix(r->GetModelMatrix() *
		Matrix4::Translation((s.V_is_UAT(u, a, t))) *
		Matrix4::Rotation(r->currentRotation, Vector3(0.f, 0.f, 1.f))
	);
}


void Movement::collisionResolution(Entity* s1, int* t1, Entity* s2, int* t2) {

	Vector3 s1Pos = s1->getPosition();
	Vector3 s2Pos = s2->getPosition();

	float m = (s2Pos.y - s1Pos.y) / (s2Pos.x - s1Pos.x);

	//angle from the x axis
	float angle = atan(m);
	float s1theta;
	float s2theta;
	if (angle >= 0) {
		s1theta = (float)M_PI_2 - angle;
		s2theta = (float)M_PI * 2.f - angle;
	}
	else {
		s1theta = (float)M_PI_2 + angle;
		s2theta = (float)M_PI * 2.f + angle;
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
	Vector3 s1u = s1->getPrevVelocity() * s1->getDamping();
	Vector3 s1a = Vector3(1 * sin(s1theta), 1 * sin(s1theta), 0) * 0.01f;
	Vector3 s2u = s2->getPrevVelocity() * s1->getDamping();
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
