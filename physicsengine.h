#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <CL/cl.h>

#include <GL/glew.h>
#include <string>
#include <vector>

#include "glengine.h"
#include "object.h"

#include "othertypes.h"


class PhysicsEngine : public GLEngine {
	cl_device_id device;
	cl_context context;
	cl_program program;
	cl_kernel kernel;
	cl_command_queue queue;


	GLuint originalPositionLocation;
	GLuint textureLocation;

	GLuint CreateProgram(const std::vector<GLuint> &);
public:
	PhysicsEngine();
	void Init();

	void Step(Object &);
};

#endif
