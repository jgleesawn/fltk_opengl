//#pragma OPENCL EXTENSION cl_khr_gl_sharing : enable

/*
__kernel void findForce(__global float4 * curPos, __local float4* force, __global float4* sumForce) {
	float4 sum;
	force[get_local_id(0)] = curPos[get_local_id(0)];
	barrier(CLK_LOCAL_MEM_FENCE);
	if(get_local_id(0) == 0) {
		sum = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
		for( int i=0; i<get_local_size(0); i++)
			sum += force[i];
		sumForce[0] = sum;
	}
}
*/

__kernel void updateVelocity(__constant float4 * curPos, __global float4* positions,
			__local float4* force, __global float4* velocities,
			__constant int * curInd, __global float4* commBuff ) {
	float3 diff,sum;
	float len,c1,c2;

	float4 cpos = positions[curInd[0]];//curPos[0];
	float4 d;
	
	int global_id = get_global_id(0);
	int local_id = get_local_id(0);
	int work_id = global_id/get_local_size(0);

if( global_id != curInd[0] ) {
	d = positions[global_id];
//	c1 = cpos.w;
	c1 = fabs(cpos.w);
//	c2 = d.w;
	c2 = -fabs(d.w);

	diff = d.xyz - cpos.xyz;
	len = length(diff);
	
	//float dist = 0.45f;
	float dist = 0.45f;
	dist = 1.0f;
	if( len < dist )
		len = dist;

	len = len*len;
	sum = -c1*c2*diff/len;
//Influence of terms changes at len = 1;
//	len = len*len;
//	sum = sum + c1*c2*(diff/len);
} else {
	sum = (float3)(0.0f, 0.0f, 0.0f);
}

	force[local_id] = (float4)(sum,0.0f);

	barrier(CLK_LOCAL_MEM_FENCE);
	
	if(local_id == 0) {
		sum = (float3)(0.0f, 0.0f, 0.0f);
		for(int i=0; i<get_local_size(0); i++)
			sum += force[i].xyz;
		commBuff[work_id].xyz = sum;
	}
	
	barrier(CLK_GLOBAL_MEM_FENCE);
	if(global_id == 0) {
		sum = (float3)(0.0f, 0.0f, 0.0f);
		for(int i=0; i<(get_global_size(0)/get_local_size(0)); i++) {
			sum += commBuff[i].xyz;
		}
		//Adds force to velocity as acceleration.
		int ci = curInd[0];
		float mass = velocities[ci].z;
		if( mass < 1.0 ) { mass = 1.0; }
		velocities[ci].xyz += sum/(mass*10000);
	}
}
/*
*/

__kernel void applyVelocity(__global float4* positions, __global float4* velocities) {
	int gi = get_global_id(0);
	positions[gi].xyz += velocities[gi].xyz;
}
/*
*/
