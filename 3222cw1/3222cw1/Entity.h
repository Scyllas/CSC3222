#pragma once

#include "../3222cw1/Vector3.h"

using namespace std;

class Entity {

public:

	Entity();
	Entity(float x, float y, float z, float a, float m);
	Entity(const Entity &obj);
	~Entity();

	float distanceBetweenSQ(Entity e);

	inline void resetEntitiesInRange() { entitiesInRange = 0; }

	inline float getX() const { return position.x; }
	inline float getY() const { return position.y; }
	inline float getZ() const { return position.z; }
	inline float getMass() { return mass; }
	inline float getAggroRange() { return aggroRange; }
	inline float getAggroRangeSQ() { return aggroRangeSQ; }
	inline int getEntitiesInRange() { return entitiesInRange; }

	inline void setX(float x) { position.x = x; }
	inline void setY(float y) { position.y = y; }
	inline void setZ(float z) { position.z = z; }
	inline void setMass(float m) { mass = m; }
	inline void setEntitiesInRange(int e) { entitiesInRange = e; }
	void setAggroRange(float r);

	friend ostream& operator<<(ostream &os, const Entity &entity);


protected:
	Vector3* prevPos;
	Vector3 position;
	float mass;
	float aggroRange;
	float aggroRangeSQ;
	int entitiesInRange;
};