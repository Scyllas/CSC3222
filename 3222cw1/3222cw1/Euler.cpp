#include "Euler.h"



Euler::Euler()
{
}


Euler::~Euler()
{
}

Vector3 Euler::expV(Vector3 u, Vector3 a, float t)
{
	return suvat.V_is_UAT(u, a, t);
	
}

Vector3 Euler::expS(Vector3 s, Vector3 v, float t)
{
	return suvat.V_is_UAT(s, v, t);
}

Vector3 Euler::semiV(Vector3 u, Vector3 a, float t)
{
	return suvat.V_is_UAT(u, a, t);
}

Vector3 Euler::semiS(Vector3 s, Vector3 v, float t)
{
	return suvat.V_is_UAT(s, v, t);
}

Vector3 Euler::impV(Vector3 u, Vector3 a, float t)
{
	return suvat.V_is_UAT(u, a, t);
}

Vector3 Euler::impS(Vector3 s, Vector3 v, float t)
{
	return suvat.V_is_UAT(s, v, t);
}

Vector3 Euler::verletV(Vector3 u, Vector3 a, float t)
{
	return suvat.V_is_UAT(u, a, t);
}

Vector3 Euler::verletS(Vector3 s, Vector3 v, float t)
{
	return suvat.V_is_UAT(s, v, t);
}

