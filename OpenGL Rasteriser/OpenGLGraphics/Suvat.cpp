#include "Suvat.h"


float Suvat::receiveNum(float f) {
	while (!(cin >> f)) {
		cout << "Bad value!\n";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	return f;
}

bool Suvat::receiveBool(bool b) {
	while (!(cin >> b)) {
		cout << "Bad value!\n";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	return b;
}

Vector3 Suvat::V_is_UAT(Vector3 u, Vector3 a, float t)
{
	return u + (a*t);
}

Vector3 Suvat::S_is_UTAT2(Vector3 u, Vector3 a, float t)
{
	return (u*t) + (((a * t) * (a * t)) * 0.5f);
}

Vector3 Suvat::S_is_UVT(Vector3 u, Vector3 v, float t)
{
	return ((u + v) * t) * 0.5f;
}

Vector3 Suvat::V2_is_U22AS(Vector3 u, Vector3 a, Vector3 s)
{
	return (u * u) + ((a * s) * 2);
}

Vector3 Suvat::S_is_VTAT2(Vector3 v, Vector3 a, float t)
{
	return (v * t) - (a * (t * t)) * 0.5f;
}



Vector3 Suvat::textInputVUAT() {

	cout << "V = U + AT" << endl;
	//	cout << "What are you trying to calculate? V, U, A, T?" << endl;

	float t = 0;
	float uX = 0;
	float uY = 0;
	float uZ = 0;
	float aX = 0;
	float aY = 0;
	float aZ = 0;

	bool check = false;


	cout << "Enter your initial speed's X" << endl;

	uX = receiveNum(uX);

	cout << "Enter your initial speed's Y" << endl;

	uY = receiveNum(uY);

	cout << "Enter your initial speed's Z" << endl;

	uZ = receiveNum(uZ);

	cout << "Enter your acceleration's X" << endl;

	aX = receiveNum(aX);

	cout << "Enter your acceleration's Y" << endl;

	aY = receiveNum(aY);

	cout << "Enter your acceleration's Z" << endl;

	aZ = receiveNum(aZ);

	cout << "Enter your time" << endl;

	t = receiveNum(t);

	cout << "Is this all correct? Enter 1 or 0" << endl;

	check = receiveBool(check);


	Vector3 u = Vector3(uX, uY, uZ);
	Vector3 a = Vector3(aX, aY, aZ);


	Vector3 at = a*t;
	Vector3 v = u + at;
	cout << "V = " << v << endl;

	int x;
	cin >> x;

	return v;
}

Vector3 Suvat::textInputSUTAT2() {

	cout << "S = UT + 1/2 AT^2" << endl;
	//	cout << "What are you trying to calculate? V, U, A, T?" << endl;

	float t = 0;
	float uX = 0;
	float uY = 0;
	float uZ = 0;
	float aX = 0;
	float aY = 0;
	float aZ = 0;
	Vector3 u;
	Vector3 a;
	bool check = false;

	cout << "Enter your initial speed's X" << endl;

	uX = receiveNum(uX);

	cout << "Enter your initial speed's Y" << endl;

	uY = receiveNum(uY);

	cout << "Enter your initial speed's Z" << endl;

	uZ = receiveNum(uZ);

	cout << "Enter your acceleration's X" << endl;

	aX = receiveNum(aX);

	cout << "Enter your acceleration's Y" << endl;

	aY = receiveNum(aY);

	cout << "Enter your acceleration's Z" << endl;

	aZ = receiveNum(aZ);

	cout << "Enter your time" << endl;

	t = receiveNum(t);

	cout << "Is this all correct? Enter 1 or 0" << endl;


	Vector3 s = (u*t) + ((a * (t * t))*0.5);
	cout << "S = " << s << endl;

	int x;
	cin >> x;

	return s;
}


