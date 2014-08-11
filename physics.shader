#version 330

layout(location = 0) in vec3 otherPosition;
layout(location = 1) in vec3 newPosition;

uniform vec3 originalPosition;


void main()
{
	vec3 diff = otherPosition-originalPosition;
	float dist = length(diff);
	newPosition = newPosition + (diff/(dist*dist));
}
