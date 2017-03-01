#pragma once
#include "../3222cw1/Vector3.h"
#include "Suvat.h"

class Euler
{
public:
	Euler();
	~Euler();


	Vector3 expV(Vector3 u, Vector3 a, float t);
	Vector3 expS(Vector3 s, Vector3 v, float t);
	
	Vector3 semiV(Vector3 u, Vector3 a, float t);
	Vector3 semiS(Vector3 s, Vector3 v, float t);

	Vector3 impV(Vector3 u, Vector3 a, float t);
	Vector3 impS(Vector3 s, Vector3 v, float t);

	Vector3 verletV(Vector3 u, Vector3 a, float t);
	Vector3 verletS(Vector3 s, Vector3 v, float t);

private:

	Suvat suvat;
};

