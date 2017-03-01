#pragma once
#include "RenderObject.h"
#include "Tile.h"

class GenerateTiles
{
public:
	GenerateTiles();
	~GenerateTiles();

	inline Tile* getTiles() {return tiles;}

private:

	Tile* tiles;
	Vector2* pixelCoord;
	Vector3* pixelColour;

};

