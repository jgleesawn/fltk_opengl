#include "physicsengine.h"

PhysicsEngine::PhysicsEngine() {
	std::vector<shaderName> shaderNames;
	shaderNames.push_back(shaderName(GL_VERTEX_SHADER, std::string("physics.shader")));
	
	InitializeProgram(shaderNames);
	
	originalPositionLocation = glGetUniformLocation(theProgram, "originalPosition");
}

PhysicsEngine::Step(Object & obj) {
	//voffset[0] += .10;
	//voffset[1] += .10;
	voffset[2] += .10;

	glUseProgram(theProgram);

	glBindBuffer(GL_ARRAY_BUFFER, obj.positionBufferObject);
	
	std::vector<Object>::iterator it;
	std::vector<Object>::iterator b = obj.position.Begin();
	int count = 1;
	for( it = obj.position.Begin(); it != obj.position.End(); it++) {
		memcpy(obj.position.Begin(), it, sizeof(*it));
		
		glUniform3f(originalPositionLocation, b[0], b[1], b[2]);

		glBufferSubData(GL_ARRAY_BUFFER, 0, 4*4, obj.position.Begin());

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4, 4*4);
		
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 4, 0);
		glVertexAttribDivisor(1, 1);

		glDrawArrays(GL_POINTS, 1, obj.position.size()-1 );

		glGetBufferSubData(GL_ARRAY_BUFFER, count*4*4, sizeof(*it), it);
	
		glDisableVertexAttribArray(0);
		glDisableVertexattribArray(1);
	}
	glUseProgram(0);
	
}


