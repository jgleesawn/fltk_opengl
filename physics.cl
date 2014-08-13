#pragma OPENCL EXTENSION cl_khr_gl_sharing : enable

__kernel void findForce(__constant float4 * curPos, __global float4* data,
			__local float4* force, __global float4* sumForce,
			__constant int * curInd ) {
	float4 diff,sum;
	float len;
	
	diff = data[get_global_id(0)]-curPos[0];
	len = length(diff);


	len = len*len;
	sum = diff/len;
//Influence of terms changes at len = 1;
	len = len*len;
	sum -= diff/len;

	force[get_local_id(0)] = sum;

	barrier(CLK_LOCAL_MEM_FENCE);
	
	if(get_local_id(0) == 0) {
		sum = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
		for(int i=0; i<get_local_size(0); i++)
			sum += force[i];
		sumForce[curInd[0]] = sum;
	}
}
