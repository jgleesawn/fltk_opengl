#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <CL/opencl.h>

#include <cstdlib>
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
	Object(PhysicsEngine *,int);

	std::vector<vec4<float> > position;
	cl_mem	cl_vbo_mem;
 
	GLuint getPBO() { return positionBufferObject; }
};

#endif
