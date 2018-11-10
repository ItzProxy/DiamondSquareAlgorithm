// DiamondSquare.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "./Dependancies/free/glut.h"
#include "DiamondSquareAlgorithm.h"
#include "sleep.h"

using namespace std;


float sd[3] = {
	0.3f,0.66f,1.0f
};

int someCounter = 0;


void init(void) {
	glClearColor(0, 0, 0, 0);
	//glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void display(void) {
	if (someCounter++ > 4) {
		someCounter = 0;
	}

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

	glBegin(GL_TRIANGLES);//start drawing triangles
	glVertex3f(-1.0f, -0.25f, sd[someCounter]);//triangle one first vertex
	glVertex3f(-0.5f, -0.25f, sd[someCounter]);//triangle one second vertex
	glVertex3f(-0.75f, 0.25f, sd[someCounter]);//triangle one third vertex
									//drawing a new triangle
	glVertex3f(0.5f, -0.25f, 0.0f);//triangle two first vertex
	glVertex3f(1.0f, -0.25f, 0.0f);//triangle two second vertex
	glVertex3f(0.75f, 0.25f, 0.0f);//triangle two third vertex
	glEnd();//end drawing of triangles
	//glutWireCube(0.6);		// size is 0.6
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

void 

int main(int argc, char **argv)
{
	clock_t start = clock();
	try {
		DiamondSquareAlgorithm p((int)std::pow(2,3) + 1);
		p.generateCorners();
		p.setSeed(time(NULL));
		p.otherDiamondSquare(p.getHeight());
		p.displayDiamondSquareArray();
		printf("\n");
		p.normalizeArray();
		p.displayDiamondSquareArray();
	}
	catch (DiamondSquareArraySizeException& ex) {
		//sizing error
		printf("%s\n", ex.what());
	}
	printf("Time elapsed: %lf\n", double(clock() - start) / CLOCKS_PER_SEC);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // single is default
	glutInitWindowSize(1000, 1000);  // default is 300 x 300
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Second OpenGL Program");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	init();
	glutMainLoop();


	return 0;
}

