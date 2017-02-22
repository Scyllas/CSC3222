#pragma once
#include "../nclgl/OGLRenderer.h"

#include "RenderObject.h"

#include <vector>

using std::vector;

class Renderer : public OGLRenderer	{

public:

	Renderer(Window &parent);
	~Renderer(void);

	GLuint LoadTexture(string filename, unsigned int flag);

	virtual void	RenderScene();

	virtual void	Render(const RenderObject &o);

	virtual void	UpdateScene(float msec);

	void	AddRenderObject(RenderObject &r) {
		renderObjects.push_back(&r);
	}

protected:

	float accumTime = 1;

	GLuint	mapTex;
	
	RenderObject spritesObject;
	
	vector<RenderObject*> renderObjects;

};

