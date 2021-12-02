#include<Windows.h>
#include<GL/glew.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include<string.h>

class Player{
public:
	Player(){}
	~Player(){}

	void drawPlayer(){
		glPushMatrix();
		{
			glScalef(1,2,1);
			glutSolidCube(1);
		}
		glPopMatrix();
	}
};
class PlayerCtrl{
public:
	GLfloat rot[3];
	GLfloat pos[3];
	GLfloat sft[3];
	GLfloat vel[3];
	GLfloat velConst;
	Player* p;
	
	PlayerCtrl(Player* p){
		this->p = p;
		//initailize the array with 0;
		memset(this->rot,0,3);
		memset(this->pos,0,3);
		memset(this->vel,0,3);
		
		velConst=-0.1;
		vel[2]=velConst;
		pos[1]=1;
	}
	~PlayerCtrl(){}

	void LookAt(){
		gluLookAt(	pos[0],pos[1]+10,pos[2]+7,
					pos[0],pos[1],pos[2]-15,
					0,1,0);
	}

	void drawPlayerCtrl(){
		glPushMatrix();
		{
			glTranslatef(pos[0],pos[1],pos[2]);
			p->drawPlayer();
		}
		glPopMatrix();
	}

	void kb(unsigned char key,int x,int y){
		if(key=='w'){
			vel[2]=velConst-0.1;
		}
		else if(key=='s'){
			vel[2]=velConst+0.05;
		}
		else if(key=='a'){
			vel[0]=velConst;
		}
		else if(key=='d'){
			vel[0]=-velConst;
		}
	}

	void kbup(unsigned char key,int x,int y){
		if(key=='w'){
			vel[2]=velConst;
		}
		else if(key=='s'){
			vel[2]=velConst;
		}
		else if(key=='a'){
			vel[0]=0;
		}
		else if(key=='d'){
			vel[0]=0;
		}
	}

	void Progress(){
		pos[0] +=vel[0];
		pos[1] +=vel[1];
		pos[2] +=vel[2];
		printf("pos.z = %f\n",pos[2]);
	}
};

Player p1;
PlayerCtrl pc1(&p1);

void drawCube(float x,float y,float z);

void init(){
	glClearColor(0.0,0.0,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

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
			glTranslatef(0,0,-500);
			glRotatef(90,1,0,0);
			glScalef(5,500,0);
			glRectf(-1,1,1,-1);
		}
		glEnable(GL_LIGHTING);
	}
	glPopMatrix();

	//cube
	drawCube(-2,1,-5);
	drawCube(3,1,-10);
	drawCube(4,1,-17);
	drawCube(4,1,-20);
	drawCube(-4,1,-50);
	drawCube(4,1,-70);
	drawCube(-2.5,1,-90);
	drawCube(4,1,-100);


	pc1.drawPlayerCtrl();
	//====================================

	glutSwapBuffers();
}

void drawCube(float x,float y,float z){
	glPushMatrix();
	{
		glTranslatef(x,y,z);
		glutSolidCube(1);
	}
	glPopMatrix();
}

void reshape(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,(GLfloat)w/(GLfloat)h,1,50);
	glMatrixMode(GL_MODELVIEW);
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

void idle(){
	pc1.Progress();
	glutPostRedisplay();
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
