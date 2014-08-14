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

__kernel void findForce(__constant float4 * curPos, __global float4* data,
			__local float4* force, __global float4* sumForce,
			__constant int * curInd ) {
	float3 diff,sum;
	float len,c1,c2;

	float4 cpos = curPos[0];
	float4 d;
	int gi = get_global_id(0);
	int li = get_local_id(0);
for(int i=0; i<4; i++){
	d = data[4*gi+i];

	c1 = cpos.w;
	c2 = d.w;

	diff = d.xyz - cpos.xyz;
	len = length(diff);

	//float dist = 0.45f;
	float dist = 0.2f;
	if( len < dist )
		len = dist;

	len = len*len;
	sum = -c1*c2*diff/len;
//Influence of terms changes at len = 1;
	len = len*len;
	sum = sum + c1*c2*(diff/len);

	force[4*li+i] = (float4)(sum,0.0f);
}

	barrier(CLK_LOCAL_MEM_FENCE);
	
	if(get_local_id(0) == 0) {
		sum = (float3)(0.0f, 0.0f, 0.0f);
		for(int i=0; i<get_local_size(0)*4; i++)
			sum += force[i].xyz;
		sumForce[curInd[0]].xyz = sum;
	}
}
/*
*/
