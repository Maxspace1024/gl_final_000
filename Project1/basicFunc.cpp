#include<Windows.h>
#include<GL/glew.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include<string.h>
#include"classDef.h"

extern Player p1;
extern PlayerCtrl pc1;

void init(){
	glClearColor(0.0,0.0,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//GLfloat lightPos[4]={1,8,1,0};
	//GLfloat lightCol[4]={2,2,2,1};
	//glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	//glLightfv(GL_LIGHT0,GL_DIFFUSE,lightCol);
}

void idle(){
	pc1.Progress();
	printf("vel.z=%f ,pos.z = %f\n",pc1.vel[2],pc1.pos[2]);
	if(pc1.isStop==0 && pc1.pos[2]<=-200 ){
		//pc1.velConst=0;
		//pc1.vel[2]=0;
		pc1.playerStop();
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key,int x,int y){
	if(key==27){
		exit(0);
	}
	pc1.kb(key,x,y);
	glutPostRedisplay();
}
void keyboardUp(unsigned char key,int x,int y){
	pc1.kbup(key,x,y);
	glutPostRedisplay();
}

void reshape(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,(GLfloat)w/(GLfloat)h,1,50);
	glMatrixMode(GL_MODELVIEW);
}