#pragma once

#include "Entity.h"
#include <time.h>  
#include "Vector3.h"
#include "Suvat.h"

#define MAX_X 10
#define MAX_Y 10
#define MAX_Z 1
#define MAX_R 5
#define NUM_ENTITIES 10



int main() {

	srand((unsigned int)time(NULL));

	Entity* eArray = new Entity[NUM_ENTITIES];

	//instantiate NUM_ENTITIES worth of Entities with random values
	for (int i = 0; i < NUM_ENTITIES; i++) {
		eArray[i] = Entity(
			(float)(rand() % MAX_X),
			(float)(rand() % MAX_Y),
			(float)(rand() % MAX_Z),
			(float)(rand() % MAX_R)
		);
	}
	/*Entity entity = Entity(
		(float)(rand() % MAX_X),
		(float)(rand() % MAX_Y),
		(float)(rand() % MAX_Z),
		(float)(rand() % MAX_R));

	eArray[0] = entity;*/

	for (int i = 0; i < NUM_ENTITIES; i++) {
		for (int j = i + 1; j < NUM_ENTITIES; j++) {
			if (eArray[i].getaggroRangeSQ() >= eArray[i].distanceBetweenSQ(eArray[j])) {
				cout << i << " aggro'd " << j << endl;
				eArray[i].setEntitiesInRange(eArray[i].getEntitiesInRange() + 1);
			}
		}
	}
	for (int i = 0; i < NUM_ENTITIES; i++) {

		cout << eArray[i] << "\t In range:" << eArray[i].getEntitiesInRange() << endl;
		eArray[i].resetEntitiesInRange();
	}

	Vector3 v = Suvat::VUAT();



}
