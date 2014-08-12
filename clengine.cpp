#include "glengine.h"

void CLEngine::CLEngine() {
	int err;
	cl_platform_id platform;
	err = clGetPlatformIDs(1, &platform, NULL);
	if(err < 0) { perror("Couldn't identify a platform, NULL); exit(1); }
	
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
	if(err == CL_DEVICE_NOT_FOUND) {
		err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, NULL);
	}
	if(err < 0) { perror("Couldn't access any devices."); exit(1); }
	
	context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
	if(err < 0) { perror("Couldn't create a context"); exit(1); }


	InitializeProgram("physics.cl");

	queue = clCreateCommandQueue(context, device, 0, &err);
	if(err < 0) { perror("Couldn't create a command queue"0; exit(1); }
	
	kernel = clCreateKernel(program, "computeForce", &err);
	
}

