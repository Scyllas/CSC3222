#define _USE_MATH_DEFINES

#include "Entity.h"

#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

//blank constructor
Entity::Entity() {

	position = Vector3();

	mass = 1;
	aggroRange = 0;
	aggroRangeSQ = 0;
	entitiesInRange = 0;

	mesh = NULL;
	shader = NULL;
	texture = NULL;
	parent = NULL;

}
//standard constructor
Entity::Entity(float x, float y, float z, float r, float ma) {

	position = Vector3(x, y, z);

	mass = ma;
	aggroRange = r;
	aggroRangeSQ = r * r;
	entitiesInRange = 0;
	scaleFactor = 1;
	diameter = 32.f;

	mesh = NULL;
	shader = NULL;
	texture = NULL;
	parent = NULL;
}

//full constructor
Entity::Entity(float x, float y, float z, float r, float ma, float sf, Mesh*m, Shader*s, GLuint t) {

	position = Vector3(x, y, z);

	mass = ma;
	aggroRange = r;
	aggroRangeSQ = r * r;
	entitiesInRange = 0;
	prevPos[50];
	scaleFactor = sf;
	diameter = 32.f * sf;
	

	mesh = m;
	shader = s;
	texture = t;
	parent = NULL;
}
//copy constructor
Entity::Entity(const Entity &obj) {

	position = Vector3(obj.position.x, obj.position.y, obj.position.z);
	mass = obj.mass;
	aggroRange = obj.aggroRange;
	aggroRangeSQ = obj.aggroRangeSQ;
	entitiesInRange = obj.entitiesInRange;

	mesh = obj.mesh;
	shader = obj.shader;
	texture = obj.texture;
	parent = obj.parent;

	modelMatrix = obj.modelMatrix;
	worldTransform = obj.worldTransform;

	parent = obj.parent;
	children = obj.children;
}



//destructor
Entity::~Entity() {
}

void Entity::setAggroRange(float r) {
	aggroRange = r;
	aggroRangeSQ = r * r;
}


float Entity::distanceBetweenSQ(Entity e) {

	return
		pow(position.x - e.position.x, 2) +
		pow(position.y - e.position.y, 2) +
		pow(position.z - e.position.z, 2);
}

ostream & operator<<(ostream & stream, const Entity & entity)
{
	stream << "Entity: (" <<
		entity.position.x << ", " <<
		entity.position.y << ", " <<
		entity.position.z << "), r = " <<
		entity.aggroRange;

	return stream;
}