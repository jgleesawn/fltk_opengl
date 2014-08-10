#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 offset;
uniform vec2 uOffset;
uniform float loopDuration;
uniform float time;

void main()
{
//	vec4 totalOffset = offset + vec4(uOffset.x,uOffset.y,0.0f,0.0f);
	float timeScale = 3.14159f * 2.0f / loopDuration;

	float currTime = mod(time, loopDuration);
	vec4 totalOffset = vec4(
		cos(currTime * timeScale) * 0.5f,
		sin(currTime * timeScale) * 0.5f,
		0.0f,
		0.0f);
	totalOffset += vec4(uOffset.x,uOffset.y,0.0f,0.0f);
	totalOffset += offset;
	gl_Position = position + totalOffset;
}
