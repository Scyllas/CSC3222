#pragma once

#include "../nclgl/Vector3.h"
#include "../OpenGLGraphics/RenderObject.h"

using namespace std;

class Entity : public RenderObject {

public:

	Entity();
	Entity(float x, float y, float z, float a, float mass);
	Entity(float x, float y, float z, float r, float mass, float sf, Mesh*m, Shader*s, GLuint t = 0);
	Entity(const Entity &obj);
	~Entity();

	float distanceBetweenSQ(Entity e);

	inline void resetEntitiesInRange() { entitiesInRange = 0; }

	inline float getX() const { return position.x; }
	inline float getY() const { return position.y; }
	inline float getZ() const { return position.z; }
	inline float getD() const { return diameter; }
	inline float getMass() { return mass; }
	inline float getAggroRange() { return aggroRange; }
	inline float getAggroRangeSQ() { return aggroRangeSQ; }
	inline float getScaleFactor() { return scaleFactor; }
	inline Vector3 getPosition() { return position; }
	inline Vector3 getPrevVelocity() { return prevVelocity; }
	inline Vector3 getPrevPos(int pp) { return prevPos[pp]; }
	inline int getEntitiesInRange() { return entitiesInRange; }
	inline bool getIsCommander() { return isCommander; }


	inline void setX(float x) { position.x = x; }
	inline void setY(float y) { position.y = y; }
	inline void setZ(float z) { position.z = z; }
	inline void setMass(float m) { mass = m; }
	inline void setEntitiesInRange(int e) { entitiesInRange = e; }
	inline void setScaleFactor(float f) { scaleFactor = f; }
	inline void setPosition(Vector3 p) { position = p; }
	inline void setPrevVelocity(Vector3 v) { prevVelocity = v; }
	inline void setIsCommander(bool b) { isCommander = b; }
	void setAggroRange(float r);
	void setPrevPos(Vector3 v);

	friend ostream& operator<<(ostream &os, const Entity &entity);


protected:
	Vector3* prevPos;
	Vector3 position;
	Vector3 prevVelocity;
	bool isCommander;
	float diameter;
	float scaleFactor;
	float mass;
	float aggroRange;
	float aggroRangeSQ;
	int entitiesInRange;
};