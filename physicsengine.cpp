#include "physicsengine.h"

PhysicsEngine::PhysicsEngine() : CLEngine() { 
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
	err = clEnqueueAcquireGLObjects(queue, 1, &obj.cl_vbo_mem, 0, NULL, NULL );
	if(err < 0) { perror("Acquire GLObject failed."); }
	
	for( int i=0; i<obj.position.size(); i++) {
		err != clSetKernelArg(kernel, 0, 4*sizeof(float), &position[i]);
		err != clSetKernelArg(kernel, 1, 4*sizeof(float)*obj.position.size(), &obj.cl_vbo_mem);
		err != clSetKernelArg(kernel, 2, 4*sizeof(float)*obj.position.size(), NULL);
		err != clSetKernelArg(kernel, 3, 4*sizeof(float), &obj.cl_vbo_mem);
		err != clSetKernelArg(kernel, 4, sizeof(int), &i);
		
		if(err != CL_SUCCESS) { perror("Error setting kernel arguments."); }
		
		int globalNum = obj.position.size();
		int localNum = globalNum;
		
		err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, globalNum, localNum, 0, NULL, NULL);
		if(err != CL_SUCCESS) { perror("Error queuing kernel for execution."); }
	}
	err = clEnqueueReleaseGLObjects(queue, 1, &obj.cl_vbo_mem, 0, NULL, NULL);
	if(err < 0) { perror("Couldn't release GLObject.") }
	clFinish(queue);
}


