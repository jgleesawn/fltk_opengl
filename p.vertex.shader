#version 330

layout(location = 0) in vec3 otherPosition;
layout(location = 1) in vec3 newPosition;
layout(location = 2) out vec3 modPosition;

uniform vec3 originalPosition;


void main()
{
	vec3 diff = otherPosition-originalPosition;
	float dist = length(diff);
	modPosition = newPosition + (diff/(dist*dist));
	gl_Position.xyz = newPosition;
}
