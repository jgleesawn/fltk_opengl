#include "visual.h"


float o = 0.5f;
float vertexPositions[] = {
	o, o, 0.0f, 1.0f,
	o, -o, 0.0f, 1.0f,
	-o, -o, 0.0f, 1.0f,
};

GLuint theProgram;
GLuint elapsedTimeUniform;
GLuint perspectiveMatrixUnif;

void InitializeProgram()
{
	std::string strVertexShader = getShaderFromFile("v.perspective.shader");	
	std::string strFragmentShader = getShaderFromFile("fragment.shader");

	std::vector<GLuint> shaderList;
	
	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, strVertexShader));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, strFragmentShader));
	
	theProgram = CreateProgram(shaderList);
	
	std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);

	GLuint FragLoopDurationUnf = glGetUniformLocation(theProgram, "fragLoopDuration");

	elapsedTimeUniform = glGetUniformLocation(theProgram, "time");

	glUseProgram(theProgram);
	glUniform1f(FragLoopDurationUnf, 2.5f);
//Could set Distance from top of window here as a uniform vector.
	glUseProgram(0);
	
//Perspective Uniform Matrix.
	perspectiveMatrixUnif = glGetUniformLocation(theProgram, "perspectiveMatrix");
	SetPerspective();
}

void SetPerspective() {
	float fFrustumScale = 1.0f; float fzNear = 0.5f; float fzFar = 3.0f;
	
	float theMatrix[16];
	memset(theMatrix, 0, sizeof(float) * 16);
	
	theMatrix[0] = fFrustumScale;
	theMatrix[5] = fFrustumScale;
	theMatrix[10] = (fzFar + fzNear) / (fzNear - fzFar);
	theMatrix[14] = (2 * fzFar * fzNear) / (fzNear - fzFar);
	theMatrix[11] = -1.0f;
	
	glUseProgram(theProgram);
	glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, theMatrix);
	glUseProgram(0);
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

