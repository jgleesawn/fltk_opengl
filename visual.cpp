#include "visual.h"


const std::string strVertexShader(
"#version 330\n"
"layout(location = 0) in vec4 position;\n"
"layout(location = 1) in vec4 offset;\n"
"void main()\n"
"{\n"
"	gl_Position = position+offset;\n"
//"	gl_Position = position;\n"
"}\n"
);


const std::string strFragmentShader(
"#version 330\n"
"out vec4 outputColor;\n"
"void main()\n"
"{\n"
"	float lerpValue = gl_FragCoord.y / 180.0f;\n"
"	outputColor = mix(vec4(1.0f, 1.0f, 1.0f, 1.0f),\n"
"			vec4(0.2f, 0.2f, 0.2f, 1.0f), lerpValue);\n"
//"	outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\n"
);

float o = 0.5f;
float vertexPositions[] = {
	o, o, 0.0f, 1.0f,
	o, -o, 0.0f, 1.0f,
	-o, -o, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
};

GLuint theProgram;

void InitializeProgram()
{
	std::vector<GLuint> shaderList;
	
	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, strFragmentShader));
	
	theProgram = CreateProgram(shaderList);
	
	std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
}

GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile) {
	GLuint shader = glCreateShader(eShaderType);
	const char *strFileData = strShaderFile.c_str();
	glShaderSource(shader, 1, &strFileData, NULL);
	
	glCompileShader(shader);
	
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
		
		const char *strShaderType = NULL;
		switch(eShaderType) {
			case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
			case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
			case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}
		
		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	 }
	 return shader;
}

GLuint CreateProgram(const std::vector<GLuint> &shaderList) {
	GLuint program = glCreateProgram();

	for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glAttachShader(program, shaderList[iLoop]);
	
	glLinkProgram(program);
	
	GLint status;
	glGetProgramiv (program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
	
	for( size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glDetachShader(program, shaderList[iLoop]);
		
	return program;
}

GLuint positionBufferObject;

void InitializeVertexBuffer() {
	glGenBuffers(1, &positionBufferObject);
	
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void ginit() {
	glewInit();
	InitializeVertexBuffer();
	InitializeProgram();
}

float voffset[] = {
	0.0f, 0.0f, 0.0f, 0.0f,
};

void display() {
	voffset[0] += .01;
	voffset[1] += .01;
	voffset[2] += .01;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(theProgram);
	
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferSubData(GL_ARRAY_BUFFER, 4*12, sizeof(voffset), &voffset);
	glBufferSubData(GL_ARRAY_BUFFER, 4*16, sizeof(voffset), &voffset);
	glBufferSubData(GL_ARRAY_BUFFER, 4*20, sizeof(voffset), &voffset);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(4*12));
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);
	
}

void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

