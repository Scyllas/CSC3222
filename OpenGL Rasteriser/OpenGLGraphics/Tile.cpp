#include "Tile.h"



Tile::Tile()
{
	coordinate = Vector2(0, 0);
	rgb = Vector3(0, 0, 0);
}

Tile::Tile(Vector2 coord, Vector3 colour){
	coordinate = coord;
	rgb = colour;
}



Tile::~Tile(){
}
