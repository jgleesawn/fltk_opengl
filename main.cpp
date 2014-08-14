#include <GL/glew.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <vector>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

#include <FL/Fl_Gl_Window.H>
//#include <FL/gl.h>

#include "physicsengine.h"
#include "visualengine.h"
#include "object.h"

void Help();

class MyWindow : public Fl_Gl_Window {
	void draw();
	int handle(int);
	
	//bool valid();
	bool v;
	int basex, basey, curx, cury;
	
	std::vector<Object> objects;
	VisualEngine ve;
	PhysicsEngine pe;
	
public:
	MyWindow(int X, int Y, int W, int H, const char *L);  
	void InitGL();
};

MyWindow::MyWindow(int X, int Y, int W, int H, const char *L)
		: Fl_Gl_Window(X, Y, W, H, L), basex(0), basey(0), curx(-2), cury(2), v(false) { Help(); }

//bool MyWindow::valid() {
//	if(!v) {
//		v = true;
//		return false;
//	}
//	return true;
//}

typedef void (*func_ptr)(void *);
void ccallback(void *);

void MyWindow::draw() {
	if( !valid() ) {
		GLenum err = glewInit(); 
		if (err != GLEW_OK) 
			exit(1);
		if (!GLEW_VERSION_3_3)
			exit(1);
		pe.Init();
		ve.Init();
		objects.push_back(Object(&pe)); //Requires glewInit to be run.

	//	ginit();
	//	ortho();
	}
/*
	glDrawBuffer(GL_FRONT_AND_BACK);
	gl_color(FL_CYAN);
	gl_rectf(basex,basey,curx,cury);
	gl_font(FL_COURIER,12);
	gl_draw("TEST",50,50);
*/
	for( std::vector<Object>::iterator it = objects.begin(); it != objects.end(); it++) {
		pe.Step(*it);
		ve.Draw(*it);
	}

	glDrawBuffer(GL_BACK);
	Fl::add_timeout(2.0, (func_ptr)ccallback, this);
}

void ccallback(void * this_ptr) {
	((MyWindow *)this_ptr)->redraw();
	
	Fl::repeat_timeout(1.0/60.0, (func_ptr)ccallback, this_ptr);
}


int MyWindow::handle(int event) {
	switch(event) {
		case FL_KEYBOARD:
			if( Fl::event_key() == 65362 ) {
//				fprintf(stderr, "up");
				basey += 1;
			}
			if( Fl::event_key() == 65364 ) {
//				fprintf(stderr, "down");
				basey -= 1;
			}
			if( Fl::event_key() == 65361 ) {
//				fprintf(stderr, "left");
				basex -= 1;
			}
			if( Fl::event_key() == 65363 ) {
//				fprintf(stderr, "right");
				basex += 1;
			}
			redraw();
//			fprintf(stderr,"%i\n",Fl::event_key());
//			fprintf(stderr,"%i %i",basex,basey);
//Escape Key
			if( Fl::event_key() == 65307 )
				exit(0);
//Zoom-in wrt scaling
			if( strcmp(Fl::event_text(),"z") == 0 ) {
				ve.voffset[2] -= .1*ve.voffset[2];
				if( !ve.voffset[2] )
					ve.voffset[2] = 0.0001;
			}
			if( strcmp(Fl::event_text(),"x") == 0 ) {
				ve.voffset[2] += .1*ve.voffset[2];
				if( !ve.voffset[2] )
					ve.voffset[2] = 0.0001;
			}
			if( strcmp(Fl::event_text(),"q") == 0 ) {
				ve.Zoom(2);
			}
			if( strcmp(Fl::event_text(),"e") == 0 ) {
				ve.Zoom(1.0/2.0);
			}
		break;
		default:
		break;
	}
}

int main(int argc, char **argv) {
	MyWindow *window = new MyWindow(20,40,300,180,"Hellow, World!");
	Fl_Box *box = new Fl_Box(20,40,260,100,"Hello, World!");
	window->show(argc, argv);
	return Fl::run();
}

void Help() {
	printf("Escape to quit.\n");
	printf("q Zooms in.(Scales frustum up)\n");
	printf("e Zooms out.(Scales frustum down)\n");
	printf("z Increases z.\n");
	printf("x Decreases z.\n");
	printf("Escape to quit.\n");
}
