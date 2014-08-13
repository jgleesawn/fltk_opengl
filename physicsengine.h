#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <CL/cl.h>
#include <CL/cl_gl.h>

#include <GL/glew.h>
#include <string>
#include <vector>

#include "glengine.h"
#include "object.h"

#include "othertypes.h"


class PhysicsEngine : public CLEngine {
public:
	PhysicsEngine();

	void Step(Object &);
};

#endif
