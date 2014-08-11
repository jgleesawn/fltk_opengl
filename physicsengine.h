#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <string>

#include "glengine.h"
#include "object.h"

class PhysicsEngine : public GLEngine() {
	GLuint originalPositionLocation;
public:
	PhysicsEngine();
	void Step(Object &);
};

#endif
