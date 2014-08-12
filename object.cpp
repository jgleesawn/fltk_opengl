#include "object.h"

Object::Object() {
	vec4<float> temp = {0.0, 0.0, 0.0, 1.0};
	position.push_back(temp);
	for( int i=0; i<10; i++) {
		temp.data[0] += .1;
		temp.data[1] += .1;
		temp.data[2] -= .1;
//		temp.data[3] += .1;
		position.push_back(temp);
	}
	InitializeVertexBuffer();
}

void Object::InitializeVertexBuffer(){
	glGenBuffers(1, &positionBufferObject);

	unsigned int size = position.size() * sizeof(struct vec4<float>);	
	
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, size, position.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
