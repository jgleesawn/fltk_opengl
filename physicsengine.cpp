#include "physicsengine.h"

PhysicsEngine::PhysicsEngine() {
	int err;
	cl_platform_id platform;
	err = clGetPlatformIDs(1, &platform, NULL);
	if(err < 0) { perror("Couldn't identify a platform, NULL); exit(1); }
	
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
	if(err == CL_DEVICE_NOT_FOUNT) {
		err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, NULL);
	}
	if(err < 0) { perror("Couldn't access any devices"); exit(1): }
	
	context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
}

GLuint PhysicsEngine::CreateProgram(const std::vector <GLuint> & shaderList) {
	GLuint program = glCreateProgram();
	
	for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glAttachShader(program, shaderList[iLoop]);
	
	const char* varyings[1] = { "modPosition" };
	glTransformFeedbackVaryings(program, 1, varyings, GL_INTERLEAVED_ATTRIBS);
		
	glLinkProgram(program);
	CheckProgram(program);
	return program;
}

//Need Init function so that the GL context is set up already;
//VE is created before GL context is set up.
void PhysicsEngine::Init() {
	std::vector<shaderName> shaderNames;
	shaderNames.push_back(shaderName(GL_VERTEX_SHADER, std::string("p.vertex.shader")));
//	shaderNames.push_back(shaderName(GL_FRAGMENT_SHADER, std::string("p.fragment.shader")));
	
	InitializeProgram(shaderNames);
	
	glGenTextures(1,&textureLocation);	
	originalPositionLocation = glGetUniformLocation(theProgram, "originalPosition");
}

void PhysicsEngine::Step(Object & obj) {
	glUseProgram(theProgram);

	glEnable(GL_RASTERIZER_DISCARD);
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

/*
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, obj.getPBO());
		glBeginTransformFeedback(GL_POINTS);
		glBindTexture(GL_TEXTURE_3D, textureLocation);
		glDrawArrays(GL_POINTS, 1, obj.position.size()-1);
		glEndTransformFeedback();
*/
//		glEnableVertexAttribArray(2);
//		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 4, 0);
//		glVertexAttribDivisor(2, 1);

		glDrawArrays(GL_POINTS, 1, obj.position.size()-1 );

		glGetBufferSubData(GL_ARRAY_BUFFER, sizeof(*it)*(it-b), sizeof(*it), it);
		
		for( int j=0; j<4; j++) {
			fprintf(stderr, "%f ", it->data[j]);
		}
		fprintf(stderr, "\n");
		
	
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
//		glDisableVertexAttribArray(2);
	}
	glDisable(GL_RASTERIZER_DISCARD);
	glUseProgram(0);
	
}


