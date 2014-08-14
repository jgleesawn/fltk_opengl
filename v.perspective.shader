#version 330

layout(location = 0) in vec4 position;

uniform vec3 uOffset;
uniform mat4 perspectiveMatrix;


void main()
{
	vec4 cameraPos = vec4( uOffset.xyz, 1.0f );
	cameraPos.xyz += position.xyz;
	gl_Position = perspectiveMatrix * cameraPos;
	//gl_Position = position; //cameraPos;
}
