#version 330

layout(location = 0) in vec4 otherPosition;
layout(location = 1) in vec3 newPosition;

uniform vec3 originalPosition;

uniform vec3 uOffset;
uniform mat4 perspectiveMatrix;


void main()
{
	vec3 diff = otherPosition-originalPosition);
	float dist = length(diff);
	newPosition = newPosition + (diff/(dist*dist));
}
