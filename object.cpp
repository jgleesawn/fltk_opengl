#include "object.h"

Object::Object() {
	float temp[4] = { 0.0, 0.0, 0.0, 1.0 };
	position.push_back(temp);
	for( int i=0; i<10; i++) {
		temp[0] += .1;
		temp[1] += .1;
		temp[2] += .1;
		temp[3] += .1;
		position.push_back(temp);
	}
	InitializeVertexBuffer();
}

void Object::InitializeVertexBuffer(){
	glGenBuffers(1, &positionBufferObject);
	
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position.Begin(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
