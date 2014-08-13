#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <CL/cl.h>
#include <CL/cl_gl.h>

#include <vector>
#include <stdio.h>

#include "othertypes.h"

class PhysicsEngine;
#include "physicsengine.h"

class Object {
	PhysicsEngine * pe;
	GLuint positionBufferObject;

	void InitializeVertexBuffer();
public:
	cl_mem	cl_vbo_mem;
	Object();
	std::vector<vec4<float> > position;

	GLuint getPBO() { return positionBufferObject; }
};

#endif
