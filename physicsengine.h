#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <GL/glew.h>
#include <string>

#include "glengine.h"
#include "object.h"

#include "othertypes.h"


class PhysicsEngine : public GLEngine {
	GLuint originalPositionLocation;
public:
	PhysicsEngine();
	void Init();

	void Step(Object &);
};

#endif
