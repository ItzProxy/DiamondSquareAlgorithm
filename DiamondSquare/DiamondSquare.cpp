// DiamondSquare.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "./Dependancies/free/glut.h"
#include "DiamondSquareAlgorithm.h"

using namespace std;

void init(void) {
	glClearColor(0, 0, 0, 0);
	//glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);	// which matrix
	glLoadIdentity();	// initialize the selected matrix
	gluLookAt(
		1.0, 2.0, 2.0,		// x,y,z of eye
		0.0, 0.0, 0.0,		// x,y,z of look at point
		0.0, 1.0, 0.0);		// x,y,z of up vector
	glPushMatrix();
	//glTranslatef(0.0, 0.0, 0.0);	// unneeded since default position is (0, 0, 0)
	//glRotatef(0.0, 1.0, 0.0, 0.0);	// unneeded since default rotation is 0 degrees
	//glScalef(1.0, 1.0, 1.0);		// unneeded since default scaling is 1 in X, Y, and Z
	glutWireCube(0.6);		// size is 0.6
	glPopMatrix();
	
	// add more stuff here to draw other models

	glFlush();
	glutSwapBuffers();		// display it, double buffering
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)w / (double)h, 0.1, 100.0);
}

int main(int argc, char **argv)
{
	clock_t start = clock();
	try {
		DiamondSquareAlgorithm p((int)std::pow(2, 12) + 1);
		p.generateCorners();
		p.setSeed(time(NULL));
		p.otherDiamondSquare(p.getHeight());
		//p.displayDiamondSquareArray();
	}
	catch (DiamondSquareArraySizeException& ex) {
		//sizing error
		printf("%s\n", ex.what());
	}
	printf("Time elapsed: %lf\n", double(clock() - start) / CLOCKS_PER_SEC);
	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // single is default
	//glutInitWindowSize(500, 500);  // default is 300 x 300
	//glutInitWindowPosition(0, 0);
	//glutCreateWindow("Second OpenGL Program");
	//glutReshapeFunc(reshape);
	//glutDisplayFunc(display);
	//init();
	//glutMainLoop();


	return 0;
}

