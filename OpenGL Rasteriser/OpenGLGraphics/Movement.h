#pragma once
#define _USE_MATH_DEFINES

#include "Tile.h"
#include "RenderObject.h"
#include "Entity.h"
#include "Suvat.h"
#include <math.h>

class Movement
{
public:
	Movement();
	~Movement();

	void collisionResolution(Entity* s1, Tile t1, Entity* s2, Tile t2);

	float sceneControls(Entity* r, Tile t);

	void move(Entity * r, float damping);

protected:
	Vector3 grassPlains;
	Vector3 field;
	Vector3 forest;
	Vector3 bridge;
	Vector3 goal;
	Vector3 wall;
	Vector3 castle;
	Vector3 start;
	Vector3 water;

	Suvat s;
};

