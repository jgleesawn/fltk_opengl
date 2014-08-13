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
	if(err < 0) { perror("Couldn't create a context."); exit(1); }


	kernel = clCreateKernel(program, "findForce", &err);
	if(err < 0) { perror("Couldn't create a kernel."); exit(1); }
	
}

void CLEngine::InitializeProgram(const char * filename) {
	int err;
	std::string progData = getFile(filename);
	int size = progData.size();
	
	program = clCreateProgramWithSource(context, 1, (const char**) &(progData.c_str())
					, &size, &err);
	if(err < 0) { perror("Couldn't create the program."); exit(1); }
	
	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if(err < 0) {
		int log_size;
		char * log;
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BULID_LOG, 0, NULL, &log_size);
		log = new char[log_size];
		clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, log_size+1, log, NULL);
		fprintf(stderr, "%s\n", log);
		delete log;
		exit(1);
	}
}

