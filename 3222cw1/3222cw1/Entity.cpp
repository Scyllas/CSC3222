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

	aggroRange = 0;
	aggroRangeSQ = 0;
	entitiesInRange = 0;

}
//standard constructor
Entity::Entity(float x, float y, float z, float r) {

	position = Vector3(x, y, z);

	aggroRange = r;
	aggroRangeSQ = r * r;
	entitiesInRange = 0;

}
//copy constructor
Entity::Entity(const Entity &obj) {

	position = Vector3(obj.position.x, obj.position.y, obj.position.z);
	aggroRange = obj.aggroRange;
	aggroRangeSQ = obj.aggroRangeSQ;
	entitiesInRange = obj.entitiesInRange;

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