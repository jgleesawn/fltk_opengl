#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <GL/glew.h>
#include <CL/cl.h>
#include <CL/cl_gl.h>

#include <string>
#include <vector>

#include "clengine.h"
#include "othertypes.h"

class Object;
#include "object.h"



class PhysicsEngine : public CLEngine {
public:
	PhysicsEngine();

	void Step(Object &);
};

#endif
