#include "clengine.h"

CLEngine::CLEngine() {
	int err;
	cl_uint np;
	cl_platform_id platform;
	err = clGetPlatformIDs(1, &platform, &np);
	fprintf(stderr, "%ui platforms available.\n", np);
	if(err < 0) { fprintf(stderr,"%i\n",err); perror("Couldn't identify a platform"); exit(1); }
	
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

	size_t size = progData.size();

	const char * data_cstr = progData.c_str();	
	program = clCreateProgramWithSource(context, 1, &data_cstr, &size, &err);
	if(err < 0) { perror("Couldn't create the program."); exit(1); }
	
	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if(err < 0) {
		size_t log_size;
		char * log;
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		log = new char[log_size];
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size+1, log, NULL);
		fprintf(stderr, "%s\n", log);
		delete log;
		exit(1);
	}
}

