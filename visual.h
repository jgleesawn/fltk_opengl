#include <GL/glew.h>

#include <algorithm>
#include <string>
#include <vector>
#include <stdio.h>
//#include <GL/gl.h>
//#include <GL/glext.h>
//#include <GL/freeglut.h>

#include "shader_util.h"

void InitializeProgram();
GLuint CreateShader(GLenum, const std::string &);
GLuint CreateProgram(const std::vector<GLuint> &);
void InitializeVertexBuffer();
void ginit();
void display();
void reshape(int, int);
