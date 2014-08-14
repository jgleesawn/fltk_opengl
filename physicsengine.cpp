#include "physicsengine.h"

PhysicsEngine::PhysicsEngine() : CLEngine() {}

void PhysicsEngine::Init() {
	_init();

	int err;
	InitializeProgram("physics.cl");
	
	queue = clCreateCommandQueue(context, device, 0, &err);
	if(err < 0) { perror("Couldn't create a command queue"); exit(1); }

	kernel = clCreateKernel(program, "findForce", &err);
	if(err < 0) { perror("Couldn't create a kernel"); exit(1); }	


	input0 = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(vec4<float>), NULL, &err);
	if(err < 0) { perror("Could not create vec4 buffer."); exit(1); }
	input4 = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int), NULL, &err);
	if(err < 0) { perror("Could not create int buffer."); exit(1); }
	

}

void PhysicsEngine::Step(Object & obj) {
	int err;
	
	glFinish();
	if(obj.cl_vbo_mem == 0 ) { return; }
	err = clEnqueueAcquireGLObjects(queue, 1, &obj.cl_vbo_mem, 0, NULL, NULL );
	if(err < 0) { perror("Acquire GLObject failed."); }

	//Returns if pointer is null
	if(obj.cl_vbo_mem == 0) { return; }
	for( int i=0; i<obj.position.size(); i++) {
		fprintf(stderr, "pos addr: %i\n", &obj.position[i]);
		for( int j=0; j<4; j++)
			fprintf(stderr, "%f ", obj.position[i].data[j]);
		fprintf(stderr, "\n");
//Added input buffers because the commented kernel args would segfault on second loop.
		clEnqueueWriteBuffer(queue, input0, CL_FALSE, 0, sizeof(vec4<float>), &obj.position[i], 0, NULL, NULL);
		clEnqueueWriteBuffer(queue, input4, CL_FALSE, 0, sizeof(int), &i, 0, NULL, NULL);
//		err  = clSetKernelArg(kernel, 0, sizeof(float), &obj.position[i]);
		err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input0);
		err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &obj.cl_vbo_mem);
		err |= clSetKernelArg(kernel, 2, 4*sizeof(float)*obj.position.size(), NULL);
		err |= clSetKernelArg(kernel, 3, sizeof(cl_mem), &obj.cl_vbo_mem);
//		err |= clSetKernelArg(kernel, 4, sizeof(int), &i);
		err |= clSetKernelArg(kernel, 4, sizeof(cl_mem), &input4);

//		err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &obj.cl_vbo_mem);
//		err |= clSetKernelArg(kernel, 1, 4*sizeof(float)*obj.position.size(), NULL);
//		err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &obj.cl_vbo_mem);
		
		if(err != CL_SUCCESS) { perror("Error setting kernel arguments."); }
		
		const size_t globalNum = obj.position.size();
		const size_t localNum = globalNum;
		
		err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalNum, &localNum, 0, NULL, NULL);
		fprintf(stderr,"%i\n",err);
		if(err != CL_SUCCESS) { perror("Error queuing kernel for execution."); exit(1); }
	}
	err = clEnqueueReleaseGLObjects(queue, 1, &obj.cl_vbo_mem, 0, NULL, NULL);
	if(err < 0) { perror("Couldn't release GLObject."); }
	clFinish(queue);

	glBindBuffer(GL_ARRAY_BUFFER, obj.getPBO());
	glGetBufferSubData(GL_ARRAY_BUFFER, 0,sizeof(vec4<float>)*obj.position.size(),obj.position.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


