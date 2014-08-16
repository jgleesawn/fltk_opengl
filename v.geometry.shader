#version 330
#extension GL_EXT_gpu_shader4: enable
#extension GL_EXT_geometry_shader4: enable

layout(points) in;
//layout(points, max_vertices = 1) out;
layout(line_strip, max_vertices = 4) out;

in float charge[];

void main() {
	gl_Position = gl_in[0].gl_Position;
	gl_Position.x += 0.01f;
	EmitVertex();

	gl_Position = gl_in[0].gl_Position;
	gl_Position.x -= 0.01f;
	EmitVertex();

	if( charge[0] == 0 ) {
		gl_Position = gl_in[0].gl_Position;
		gl_Position.y += .01;
		EmitVertex();
	}

	if( charge[0] > 0 ) {
		EndPrimitive();
		gl_Position = gl_in[0].gl_Position;
		gl_Position.y += .01;
		//gl_Position.x -= .01;
		EmitVertex();

		gl_Position = gl_in[0].gl_Position;
//		gl_Position.xy += .01;
		gl_Position.y -= .01;
		EmitVertex();
	}
	
	EndPrimitive();
/*
*/
}
