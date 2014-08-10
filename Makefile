CC=g++
INCLUDES=-I/home/tc/fltk-1.3.2/ -I/home/tc/freeglut-2.8.1/include -I/home/tc/glew-1.10.0/include
LIB_PATH=-L/home/tc/fltk-1.3.2/lib/ -L/home/tc/freeglut-2.8.1/src/.libs -L/home/tc/glew-1.10.0/lib
LIBS=-lfltk -lfltk_gl -lGL -lglut -lGLEW
LIBS1.3=-ldl -lXft -lXinerama

FILES=main.cpp visual.cpp

all:
	$(CC) $(FILES) $(INCLUDES) $(LIB_PATH) $(LIBS) $(LIBS1.3)
debug:
	$(CC) -g $(FILES) $(INCLUDES) $(LIB_PATH) $(LIBS) $(LIBS1.3)

