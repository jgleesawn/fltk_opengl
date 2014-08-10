#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 offset;
uniform vec2 uOffset;

void main()
{
	vec4 totalOffset = offset + vec4(uOffset.x, uOffset.y, 0.0, 0.0);
	gl_Position = position + totalOffset;
}
