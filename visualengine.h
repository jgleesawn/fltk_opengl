#ifndef VISUALENGINE_H
#define VISUALENGINE_H

#include <GL/glew.h>
#include <string>

#include "glengine.h"
#include "object.h"

class VisualEngine : public GLEngine {
	void SetPerspective();

	GLuint perspectiveMatrixUnif;
	GLuint elapsedTimeUniform;

	GLuint offsetLocation;

	float voffset[4];
public:
	VisualEngine();
	void Init();

	void Draw(Object &);

	void reshape(int, int);
};

void ginit();
void display();

#endif
