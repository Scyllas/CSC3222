#pragma once

#include <iostream>
#include "../nclgl/Vector3.h"
#include "Windows.h"

using namespace std;

class Suvat {

public:
	float static receiveNum(float f);
	bool static receiveBool(bool b);
	Vector3 V_is_UAT(Vector3 u, Vector3 a, float t);
	Vector3 S_is_UTAT2(Vector3 u, Vector3 a, float t);
	Vector3 S_is_UVT(Vector3 u, Vector3 v, float t);
	Vector3 V2_is_U22AS(Vector3 u, Vector3 a, Vector3 s);
	Vector3 S_is_VTAT2(Vector3 v, Vector3 a, float t);



	Vector3 static textInputVUAT();
	Vector3 static textInputSUTAT2();

private:



};