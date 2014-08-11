#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "glengine.h"
#include "object.h"

class PhysicsEngine : public GLEngine() {
public:
	PhysicsEngine();
	void Step(Object &);
};

void ginit();
void display();
void reshape(int, int);

void SetPerspective();

#endif
