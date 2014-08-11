#include VISUALENGINE_H
#define VISUALENGINE_H

#include <string>

#include "glengine.h"
#include "object.h"

class VisualEngine : public GLEngine {
	void SetPerspective();

	GLuint perspectiveMatrixUnif;
	GLuint elapsedTimeUniform;

	Gluint offsetLocation;

	float voffset[4];
public:
	VisualEngine();
	void Draw(Object &);

	void SetPerspective();
	void reshape(int, int);
};

void ginit();
void display();

#endif
