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
		err != clSetKernelArg(kernel, 0, sizeof(vec4<float>), &obj.position[i]);
		//err != clSetKernelArg(kernel, 1, sizeof(cl_mem), &obj.cl_vbo_mem);
		err != clSetKernelArg(kernel, 1, sizeof(vec4<float>)*obj.position.size(), &obj.cl_vbo_mem);
		err != clSetKernelArg(kernel, 2, sizeof(vec4<float>)*obj.position.size(), NULL);
		err != clSetKernelArg(kernel, 3, sizeof(vec4<float>)*obj.position.size(), &obj.cl_vbo_mem);
		err != clSetKernelArg(kernel, 4, sizeof(int), &i);
		
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
}


