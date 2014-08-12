#include "physicsengine.h"

PhysicsEngine::PhysicsEngine() {}

//Need Init function so that the GL context is set up already;
//VE is created before GL context is set up.
void PhysicsEngine::Init() {
	std::vector<shaderName> shaderNames;
	shaderNames.push_back(shaderName(GL_VERTEX_SHADER, std::string("p.vertex.shader")));
	shaderNames.push_back(shaderName(GL_FRAGMENT_SHADER, std::string("p.fragment.shader")));
	
	InitializeProgram(shaderNames);
	
	originalPositionLocation = glGetUniformLocation(theProgram, "originalPosition");
}

void PhysicsEngine::Step(Object & obj) {
	glUseProgram(theProgram);

	glBindBuffer(GL_ARRAY_BUFFER, obj.getPBO());
	
	vec4<float> * it;
	vec4<float> * b = obj.position.data();
	for( it = b+1; it < b+obj.position.size(); it++ ) {
		memcpy(b, it, sizeof(*it));
		
		glUniform3f(originalPositionLocation, b->data[0], b->data[1], b->data[2]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 4*4, b);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4, (GLvoid*)sizeof(*it));
		
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 4, 0);
		glVertexAttribDivisor(1, 1);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 4, 0);
		glVertexAttribDivisor(2, 1);

		glDrawArrays(GL_POINTS, 1, obj.position.size()-1 );

		glGetBufferSubData(GL_ARRAY_BUFFER, sizeof(*it)*(it-b), sizeof(*it), it);
		
		for( int j=0; j<4; j++) {
			fprintf(stderr, "%f ", it->data[j]);
		}
		fprintf(stderr, "\n");
		
	
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
	glUseProgram(0);
	
}


