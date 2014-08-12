#version 330

layout(location = 0) in vec4 position;

uniform vec3 uOffset;
uniform mat4 perspectiveMatrix;


void main()
{
	vec4 cameraPos = position + vec4( uOffset.x, uOffset.y, uOffset.z, 0.0f);
	gl_Position = perspectiveMatrix * cameraPos;
	//gl_Position = position; //cameraPos;
}
