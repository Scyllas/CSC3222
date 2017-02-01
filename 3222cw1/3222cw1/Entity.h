#pragma once

#include "Vector3.h"

using namespace std;

class Entity {

public:

	Entity();
	Entity(float x, float y, float z, float a);
	Entity(const Entity &obj);
	~Entity();

	inline void resetEntitiesInRange() { entitiesInRange = 0; }
	float distanceBetweenSQ(Entity e);

	inline float getX() const { return position->x; }
	inline float getY() const { return position->y; }
	inline float getZ() const { return position->z; }
	inline float getaggroRange() { return aggroRange; }
	inline float getaggroRangeSQ() { return aggroRangeSQ; }
	inline int getEntitiesInRange() { return entitiesInRange; }

	inline void setX(float x) { position->x = x; }
	inline void setY(float y) { position->y = y; }
	inline void setZ(float z) { position->z = z; }
	inline void setEntitiesInRange(int e) { entitiesInRange = e; }
	void setAggroRange(float r);

	friend ostream& operator<<(ostream &os, const Entity &entity);

 
protected:

	Vector3* position;
	float aggroRange;
	float aggroRangeSQ;
	int entitiesInRange;
};