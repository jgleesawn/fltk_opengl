#ifndef CLENGINE_H
#define CLENGINE_H

#include <CL/cl.h>

#include <string.h>

#include <algorithm>
#include <string>
#include <vector>
#include <stdio.h>


#include "shader_util.h"

class CLEngine {
protected:
	cl_device_id device;
	cl_context context;
	cl_program program;
	cl_kernel kernel;
	cl_command_queue queue;

	void InitializeProgram(const char *);
	void InitializeProgram(std::vector<shaderName> &);
	GLuint CreateShader(GLenum, const std::string &);
	GLuint CreateProgram(const std::vector<GLuint> &);
	void   CheckProgram(GLuint &);
public:
	CLEngine();

};


#endif
