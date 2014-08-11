#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <vector>

class Object {
	GLuint positionBufferObject;
	void InitializeVertexBuffer();
public:
	Object();
	std::vector<float[4]> position;
};

#endif
