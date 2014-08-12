CC=g++
INCLUDES=-I./fltk-1.3.2/ -I./glew-1.10.0/include -I./include
LIB_PATH=-L./fltk-1.3.2/lib/ -L./glew-1.10.0/lib
LIBS=-lfltk -lfltk_gl -lGL -lGLEW -lGLU
LIBS1.3=-ldl -lXft -lXinerama
LIBSCL=-lOpenCL

FILES=main.cpp glengine.cpp shader_util.cpp physicsengine.cpp visualengine.cpp object.cpp

all:
	$(CC) $(FILES) $(INCLUDES) $(LIB_PATH) $(LIBS) $(LIBS1.3) $(LIBSCL)
debug:
	$(CC) -g $(FILES) $(INCLUDES) $(LIB_PATH) $(LIBS) $(LIBS1.3) $(LIBSCL)

