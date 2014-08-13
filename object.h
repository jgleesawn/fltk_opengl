#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>

#include <CL/cl.h>
#include <CL/cl_gl.h>

#include <vector>

#include "physicsengine.h"
#include "othertypes.h"


class Object {
	PhysicsEngine * pe;
	GLuint positionBufferObject;
	cl_mem	cl_vbo_mem;

	void InitializeVertexBuffer();
public:
	Object();
	std::vector<vec4<float> > position;

	GLuint getPBO() { return positionBufferObject; }
};

#endif
