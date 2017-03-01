#pragma once
#include "../nclgl/Vector2.h"
#include "../nclgl/Vector3.h"

class Tile
{
public:
	Tile();
	Tile(Vector2 coord, Vector3 colour);
	~Tile();

	inline Vector2 getCoordinate() { return coordinate; }
	inline Vector3 getRGB() { return rgb; }
private:

	Vector2 coordinate;
	Vector3 rgb;

};

