#pragma once
#define _USE_MATH_DEFINES
#define SCALE_FACTOR 0.05f
#define SIZE_OF_ARRAYPOINTS 8.f
#define SCALE_OVER_ARRAYSIZE SCALE_FACTOR / SIZE_OF_ARRAYPOINTS
#define cos45 cos(M_PI_4)

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

	void collisionResolution(Entity* s1, int* t1, Entity* s2, int* t2);

	void sceneControls(Entity* r, int* tileLoc, Tile* t, float rad);

	void move(Entity * r, bool isWall);

	void displace(Entity* r, Vector3 u, Vector3 a, float t);

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

