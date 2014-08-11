#include "visual.h"

VisualEngine::VisualEngine() {
	std::vector<shaderName> shaderNames;
	shaderNames.push_back(shaderName(GL_VERTEX_SHADER, std::string("v.perspective.shader")));
	shaderNames.push_back(shaderName(GL_FRAGMENT_SHADER, std::string("fragment.shader")));

	InitializeProgram(shaderNames);

	offsetLocation = glGetUniformLocation(theProgram, "uOffset");
	perspectiveMatrixUnif = glGetUniformLocation(theProgram, "perspectiveMatrix");

	SetPerspective();
}

void VisualEngine::SetPerspective() {
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

void VisualEngine::Draw(Object & obj) {
	//voffset[0] += .10;
	//voffset[1] += .10;
	voffset[2] += .10;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(theProgram);

	glUniform3f(offsetLocation, -voffset[0], -voffset[1], -voffset[2]);
	
	glBindBuffer(GL_ARRAY_BUFFER, obj.positionBufferObject);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 1, obj.position.size()-1);
	
	glDisableVertexAttribArray(0);
	glUseProgram(0);
	
}

void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

