#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <GL/glew.h>
#include <CL/opencl.h>

#include <string>
#include <vector>

#include "clengine.h"
#include "othertypes.h"

class Object;
#include "object.h"



class PhysicsEngine : public CLEngine {
	cl_mem input0;
	cl_mem input4;
public:
	PhysicsEngine();
	void Init();

	void Step(Object &);
};

#endif
