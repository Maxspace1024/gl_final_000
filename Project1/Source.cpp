#include<Windows.h>
#include<GL/glew.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include<string.h>
#define _USE_MATH_DEFINES
#include<math.h>

#include"basicFunc.h"
#include"classDef.h"

extern Player p1=Player();
extern PlayerCtrl pc1(&p1);

void display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	pc1.LookAt();
	//====================================
	
	//ground
	glPushMatrix();
	{
		glDisable(GL_LIGHTING);
		{
			glColor3ub(80,127,80);
			glTranslatef(0,0,-100);
			glRotatef(90,1,0,0);
			glScalef(6,150,0);
			glRectf(-1,1,1,-1);
		}
		glEnable(GL_LIGHTING);
	}
	glPopMatrix();

	//cube
	//static method ,don't need instance
	TestObject::drawCube(-2,1,-5);
	TestObject::drawCube(3,1,-10);
	TestObject::drawCube(4,1,-20);
	TestObject::drawCube(-4,1,-50);
	TestObject::drawCube(4,1,-70);
	TestObject::drawCube(-2.5,1,-90);
	TestObject::drawCube(4,1,-100);
	TestObject::drawCube(4,1,-130);
	TestObject::drawCube(4,1,-200);


	pc1.drawPlayerCtrl();
	//====================================

	glutSwapBuffers();
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH |GLUT_MULTISAMPLE);
	glutInitWindowPosition(300,300);
	glutInitWindowSize(700,700);
	glutCreateWindow("TITLE");

	init();

	GLenum err = glewInit();
	if( err != GLEW_OK){
		printf("GLEW_ERROR\n");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
