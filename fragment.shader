#version 330

out vec4 outputColor;

uniform float fragLoopDuration;
uniform float time;

const vec4 firstColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
const vec4 secondColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);

varying float scalar;


void main()
{
	float currTime = mod(time, fragLoopDuration);
	float currLerp = currTime / fragLoopDuration;

	outputColor = mix(firstColor, secondColor, currLerp);
	outputColor[0] *= scalar;
	outputColor[1] *= scalar;
//	float lerpValue = gl_FragCoord.y / 180.0f;
//	outputColor = mix(vec4(1.0f, 1.0f, 1.0f, 1.0f),
//			vec4(0.2f, 0.2f, 0.2f, 1.0f), lerpValue);
}
