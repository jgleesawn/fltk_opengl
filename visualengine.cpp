#include "visualengine.h"

void VisualEngine::Zoom(float s) {
	scale *= s;
	SetPerspective();
}
VisualEngine::VisualEngine() {
	voffset[0] = 0.0f;
	voffset[1] = 0.0f;
	voffset[2] = 0.0f;
	voffset[3] = 0.0f;
}

//Need Init function so that the GL context is set up already;
//VE is created before GL context is set up.
void VisualEngine::Init() {
	std::vector<shaderName> shaderNames;
	shaderNames.push_back(shaderName(GL_VERTEX_SHADER, std::string("v.perspective.shader")));
	shaderNames.push_back(shaderName(GL_FRAGMENT_SHADER, std::string("v.fragment.shader")));

	InitializeProgram(shaderNames);

	
	offsetLocation = glGetUniformLocation(theProgram, "uOffset");
	perspectiveMatrixUnif = glGetUniformLocation(theProgram, "perspectiveMatrix");


	elapsedTimeUniform = glGetUniformLocation(theProgram, "time");
	fragLoopDuration = glGetUniformLocation(theProgram, "fragLoopDuration");

	scale = 1.0f;
	SetPerspective();

	glUseProgram(theProgram);
	glUniform1f(fragLoopDuration, (GLfloat)2.5f);
	glUseProgram(0);

	voffset[2] = 30.0;
}

void VisualEngine::SetPerspective() {
	float fFrustumScale = scale; float fzNear = 0.1f; float fzFar = 100000.0f;
	
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

void VisualEngine::Draw(Object & obj) {
	GLenum glerr = glGetError();
	if( glerr != 0 )
		fprintf(stderr, "%s\n", gluErrorString(glerr));

	//voffset[0] += .10;
	//voffset[1] += .10;
	//voffset[2] += .10;
//	voffset[2] = 30.0;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(theProgram);

	glUniform1f(elapsedTimeUniform, voffset[2]);
	glUniform3f(offsetLocation, -voffset[0], -voffset[1], -voffset[2]);
	
	glBindBuffer(GL_ARRAY_BUFFER, obj.getPBO());

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(4*4));
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//glDrawArrays(GL_TRIANGLE_STRIP, 1, obj.position.size()-1);
	glDrawArrays(GL_POINTS, 1, obj.position.size()-1);
	
	glDisableVertexAttribArray(0);
	glUseProgram(0);
	
}

void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

