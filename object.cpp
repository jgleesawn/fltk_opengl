#include "object.h"
//num used to be constant at 1024
Object::Object(PhysicsEngine * pep,int num) {
//Velocity buffer.
	vec4<float> *buf;
	buf = new vec4<float>[num];
	memset(buf,0,sizeof(vec4<float>)*num);

	pe = pep;
	vec4<float> temp = {0.0, 0.0, 0.0, 0.0};
	//position.push_back(temp);
	//buf[0].data[3] = 1000000*1;	//10^6 neutron core to see how it affects particles.	
	for( int i=0; i<num; i++) {
		for( int j=0; j<3; j++) {
			temp.data[j] = rand()%100 - 50;
			temp.data[j] /= 20;
		}
		temp.data[3] = 1*(rand()%3-1);//limit of one charge.
//		temp.data[3] = -1;//all electrons.
		position.push_back(temp);

// charge/mass ratio = 10^5 and 5x10^7
// usually ~10^8 and 10^11
		if( temp.data[3] > 0 ) {
			int mult = rand()%4;
			buf[i].data[3] = mult*1.0f;
			position[i].data[3] *= mult;
		}
		else if( temp.data[3] == 0 )
			buf[i].data[3] = 1.0f;
		else
			buf[i].data[3] = 0.001f;
	}
/*
	for( int i=0; i<num/2; i++) {
		for( int j=0; j<4; j++) {
			temp.data[j] = rand()%100 + 50;
			temp.data[j] /= 20;
		}
		temp.data[3] = rand()%9-4;
		position.push_back(temp);

		if( temp.data[3] >= 0 )
			buf[num/2 + i].data[3] = 1.0f;
		else
			buf[num/2 + i].data[3] = 0.001f;
	}
*/
	InitializeVertexBuffer();

//	glFinish();
	int err;
//	cl::BufferGL(pe->getContext(), CL_MEM_READ_WRITE, positionBufferObject, &err);

	cl_vbo_mem = clCreateFromGLBuffer(pe->getContext(), CL_MEM_READ_WRITE, positionBufferObject, &err);
	fprintf(stderr,"%i\n",err);
	if(err != CL_SUCCESS) { perror("Couldn't create CLbuffer from GLbuffer."); cl_vbo_mem = 0;}

	cl_vel_mem = clCreateBuffer(pe->getContext(), CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, 4*sizeof(cl_float)*position.size(), buf, &err);
	if(err != CL_SUCCESS) { perror("Couldn't create velocity CLbuffer."); cl_vbo_mem = 0;}
	delete buf;
}

void Object::InitializeVertexBuffer(){
	glGenBuffers(1, &positionBufferObject);

	unsigned int size = position.size() * sizeof(struct vec4<float>);	
	
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, size, position.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
