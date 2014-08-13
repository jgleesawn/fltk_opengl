#include "clengine.h"

CLEngine::CLEngine() {}
void CLEngine::_init() {
	int err;
	cl_uint np;
	cl_platform_id platform;
	err = clGetPlatformIDs(1, &platform, &np);
	if(err < 0) { fprintf(stderr,"%i\n",err); perror("Couldn't identify a platform"); exit(1); }

	size_t size;
	char params[500];
	clGetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS, 500,params,&size);
	fprintf(stderr,"%s\n",params);

	
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
	if(err == CL_DEVICE_NOT_FOUND) {
		err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, NULL);
	}
	if(err < 0) { perror("Couldn't access any devices."); exit(1); }

	clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, 500,params,&size);
	fprintf(stderr,"%s\n",params);

	fprintf(stderr,"%i %i\n",glXGetCurrentContext(), glXGetCurrentDisplay());
	cl_context_properties properties[] = 
	{
		CL_GL_CONTEXT_KHR, (cl_context_properties) glXGetCurrentContext(),
		CL_GLX_DISPLAY_KHR, (cl_context_properties) glXGetCurrentDisplay(),
		CL_CONTEXT_PLATFORM, (cl_context_properties) platform,
		0
	};
	context = clCreateContext(properties, 1, &device, NULL, NULL, &err);
	fprintf(stderr,"%i\n",err);
	if(err < 0) { perror("Couldn't create a context."); exit(1); }
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

