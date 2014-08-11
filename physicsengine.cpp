#include "physicsengine.h"


float o = 0.5f;
float vertexPositions[] = {
	o, o, 0.0f, 1.0f,
	o, -o, 0.0f, 1.0f,
	-o, -o, 0.0f, 1.0f,
};

GLuint offsetLocation;

void ginit() {
	glewInit();
	InitializeVertexBuffer();
	InitializeProgram();
	offsetLocation = glGetUniformLocation(theProgram, "uOffset");
}

float voffset[] = {
	0.0f, 0.0f, 0.0f, 0.0f,
};

void display() {
	//voffset[0] += .10;
	//voffset[1] += .10;
	voffset[2] += .10;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(theProgram);

	glUniform3f(offsetLocation, -voffset[0], -voffset[1], -voffset[2]);
	
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glDisableVertexAttribArray(0);
	glUseProgram(0);
	
}

void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

