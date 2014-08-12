#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <vector>

#include <cmath>


#include "othertypes.h"


class Object {
	GLuint positionBufferObject;
	void InitializeVertexBuffer();
public:
	Object();
	std::vector<vec4<float> > position;

	GLuint getPBO() { return positionBufferObject; }
};

#endif
