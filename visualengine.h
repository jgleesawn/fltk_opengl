#include VISUALENGINE_H
#define VISUALENGINE_H

#include "glengine.h"
#include "object.h"

class VisualEngine : public GLEngine {
public:
	VisualEngine();
	void Draw(Object &);
};

void ginit();
void display();
void reshape(int, int);

void SetPerspective();

#endif
