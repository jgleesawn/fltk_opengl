#ifndef GLENGINE_H
#define GLENGINE_H

#include <GL/glew.h>

#include <string.h>

#include <algorithm>
#include <string>
#include <vector>
#include <stdio.h>

#include <utility>	//For pair

//#include <GL/gl.h>
//#include <GL/glext.h>
//#include <GL/freeglut.h>

#include "shader_util.h"

typedef std::pair<GLenum,std::string> shaderName;
class GLEngine {
protected:
	GLuint theProgram;

	void InitializeProgram(std::vector<shaderName> &);
	GLuint CreateShader(GLenum, const std::string &);
	GLuint CreateProgram(const std::vector<GLuint> &);
public:

};


#endif
