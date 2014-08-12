#version 330

layout(location = 2) out vec4 outputColor;

const vec4 firstColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
const vec4 secondColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);

void main()
{
	outputColor = mix(firstColor, secondColor, .5);
	//outputColor[0] *= scalar;
	//outputColor[1] *= scalar;
//	float lerpValue = gl_FragCoord.y / 180.0f;
//	outputColor = mix(vec4(1.0f, 1.0f, 1.0f, 1.0f),
//			vec4(0.2f, 0.2f, 0.2f, 1.0f), lerpValue);
}
