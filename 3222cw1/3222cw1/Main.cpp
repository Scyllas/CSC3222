
#include "Entity.h"
#include <time.h>  

#define MAX_X 10
#define MAX_Y 10
#define MAX_Z 10
#define MAX_R 5
#define NUM_ENTITIES 10

int main() {

	srand((unsigned int)time(NULL));

	Entity* eArray = new Entity[NUM_ENTITIES];

	//instantiate NUM_ENTITIES worth of Entities with random values
	for (int i = 0; i < NUM_ENTITIES; i++) {
		eArray[i] = Entity(
			rand() % MAX_X,
			rand() % MAX_Y,
			rand() % MAX_Z,
			rand() % MAX_R
		);
	}

	for (int i = 0; i < NUM_ENTITIES; i++) {
		for (int j = i + 1; j < NUM_ENTITIES; j++) {
			if (eArray[i].getaggroRangeSQ() <= eArray[i].distanceBetweenSQ(eArray[j])) {
				cout << i << " aggro'd " << j << endl;
				eArray[i].setEntitiesInRange(eArray[i].getEntitiesInRange() + 1);
			}
		}
	}
	for (int i = 0; i < NUM_ENTITIES; i++) {
	
		cout << eArray[i] << eArray[i].getEntitiesInRange() << endl;
	
	}

	int x;
	cin >> x;
}