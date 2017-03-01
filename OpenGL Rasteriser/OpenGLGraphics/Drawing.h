#pragma once
#include "RenderObject.h"
#include "Entity.h"
#include "Renderer.h"

class Drawing
{
public:

	RenderObject drawMap(Mesh * m, Renderer & r, Shader * s);

	Entity * drawSoldier(Mesh * m, Renderer & r, Shader * s);

	Entity drawCommander(Mesh * m, Renderer & r, Shader * s);

};

