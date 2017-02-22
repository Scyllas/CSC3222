#pragma once

#include "Entity.h"
#include <time.h>  
#include "../nclgl/Vector3.h"
#include "Suvat.h"
#include "../nclgl/GameTimer.h"
#include "Renderer.h"
#include "RenderObject.h"

#pragma comment(lib, "nclgl.lib")

#define MAX_X 10
#define MAX_Y 10
#define MAX_Z 1
#define MAX_R 5
#define NUM_ENTITIES 10



int main2() {

	srand((unsigned int)time(NULL));

	int dimensions = 800;
	Window w = Window(dimensions, dimensions);
	Renderer r(w);

	LARGE_INTEGER frequency, start;
	QueryPerformanceCounter(&frequency);
	QueryPerformanceCounter(&start);


	Entity* eArray = new Entity[NUM_ENTITIES];

	//instantiate NUM_ENTITIES worth of Entities with random values
	for (int i = 0; i < NUM_ENTITIES; i++) {
		eArray[i] = Entity(
			(float)(rand() % MAX_X),
			(float)(rand() % MAX_Y),
			(float)(rand() % MAX_Z),
			(float)(rand() % MAX_R),
			1.0f
		);
	}

	for (int i = 0; i < NUM_ENTITIES; i++) {
		for (int j = i + 1; j < NUM_ENTITIES; j++) {
			if (eArray[i].getAggroRangeSQ() >= eArray[i].distanceBetweenSQ(eArray[j])) {
				cout << i << " aggro'd " << j << endl;
				eArray[i].setEntitiesInRange(eArray[i].getEntitiesInRange() + 1);
			}
		}
	}
	for (int i = 0; i < NUM_ENTITIES; i++) {

		cout << eArray[i] << "\t In range:" << eArray[i].getEntitiesInRange() << endl;
		eArray[i].resetEntitiesInRange();
	}


	return 0;

}
