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

class MyWindow : public Fl_Gl_Window {
	void draw();
	int handle(int);
	
	bool valid();
	bool v;
	int basex, basey, curx, cury;
	
	std::vector<Object> objects;
	VisualEngine ve;
	PhysicsEngine pe;

public:
	MyWindow(int X, int Y, int W, int H, const char *L)  
		: Fl_Gl_Window(X, Y, W, H, L),basex(0),basey(0),curx(-2),cury(2),v(false)  {  }
	void InitGL();
};

bool MyWindow::valid() {
	if(!v) {
		v = true;
		return false;
	}
	return true;
}

void MyWindow::draw() {
	if( !valid() ) {
		GLenum err = glewInit(); 
		if (err != GLEW_OK) 
			exit(1);
		if (!GLEW_VERSION_3_3)
			exit(1);
		pe.Init();
		ve.Init();
		objects.push_back(Object()); //Requires glewInit to be run.

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
		for( int i=0; i<(*it).position.size(); i++) {
			for( int j=0; j<4; j++){
				//fprintf(stderr,"%f ", (*it).position[i].data[j]);
			}
			//fprintf(stderr,"\n");
		}
		ve.Draw(*it);
	}

	glDrawBuffer(GL_BACK);
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
			if( strcmp(Fl::event_text(),"q") == 0 ) {
				exit(0);
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
