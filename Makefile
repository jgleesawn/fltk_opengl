CC=g++
INCLUDES=-I./fltk-1.3.2/ -I./glew-1.10.0/include
LIB_PATH=-L./fltk-1.3.2/lib/ -L./glew-1.10.0/lib
LIBS=-lfltk -lfltk_gl -lGL -lGLEW
LIBS1.3=-ldl -lXft -lXinerama

FILES=main.cpp visual.cpp shader_util.cpp

all:
	$(CC) $(FILES) $(INCLUDES) $(LIB_PATH) $(LIBS) $(LIBS1.3)
debug:
	$(CC) -g $(FILES) $(INCLUDES) $(LIB_PATH) $(LIBS) $(LIBS1.3)

