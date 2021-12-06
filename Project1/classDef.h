#pragma once
#include<Windows.h>
#include<GL/glew.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include<string.h>
#define _USE_MATH_DEFINES
#include<math.h>

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
	GLfloat rot[3];		//rotation
	GLfloat sft[3];		//Position shift
	GLfloat pos[3];		//Position
	GLfloat vel[3];		//Velocity
	GLfloat acc[3];		//Acceleration
	GLfloat velConst;
	Player* p;

	GLfloat sftStep[3];
	GLint isStop=0;

	PlayerCtrl(Player* p){
		this->p = p;
		//initailize the array with 0;
		//memset() is in <string.h>
		memset(this->rot,0,3);
		memset(this->sft,0,3);
		memset(this->sftStep,0,3);
		memset(this->pos,0,3);
		memset(this->vel,0,3);

		sftStep[2]=0.05;

		velConst=-0.25;
		vel[2]=velConst;
		pos[1]=1;
	}
	~PlayerCtrl(){}

	void LookAt(){
		gluLookAt(	
			pos[0],pos[1]+5,pos[2]+5,
			pos[0],pos[1],pos[2]-17,
			0,1,0);
	}

	void drawPlayerCtrl(){
		glPushMatrix();
		{
			//glTranslatef(pos[0],pos[1],pos[2]+sft[2]);
			glTranslatef(pos[0],pos[1],pos[2]);
			p->drawPlayer();
		}
		glPopMatrix();
	}

	void kb(unsigned char key,int x,int y){
		if(key=='w'){
			vel[2]=velConst*1.2;
			//if(sft[2]>-0.5) sft[2]-=sftStep[2];
		}
		else if(key=='s'){
			vel[2]=velConst*0.8;
			//if(sft[2]<0.5) sft[2]+=sftStep[2];
		}
		else if(key=='a'){
			vel[0]=velConst*0.7;
		}
		else if(key=='d'){
			vel[0]=-velConst*0.7;
		}
	}

	void playerStop(){
		velConst=0;
		vel[2]=0;
		isStop=1;
	}

	void kbup(unsigned char key,int x,int y){
		if(key=='w'){
			vel[2]=velConst;
			//if(sft[2]<0) sft[2]+=sftStep[2];
		}
		else if(key=='s'){
			vel[2]=velConst;
			//if(sft[2]>0) sft[2]-=sftStep[2];
		}
		else if(key=='a'){
			vel[0]=0;
		}
		else if(key=='d'){
			vel[0]=0;
		}
	}

	void Progress(){
		pos[0]+=vel[0];
		pos[1]+=vel[1];
		pos[2]+=vel[2];
	}
};

class Building{
public:
	GLfloat bdScale[3];

	Building(GLfloat x,GLfloat y,GLfloat z,int randSeed){
		bdScale[0]=x;
		bdScale[1]=y;
		bdScale[2]=z;
	}
	~Building(){}

	void drawBuilding(){
	
	}
};

class Event{
public:
	//check the object in Event if collides with player
	PlayerCtrl* p1;

	Event(PlayerCtrl* p){
		p1 = p;
	}
	~Event(){}

	int isCollide(){

		return 0;
	}
};

class CollisionBall{
public:
	GLfloat csCenter[3];
	GLfloat csRadius;

	CollisionBall(GLfloat x,GLfloat y,GLfloat z,GLfloat r){
		csCenter[0]=x;
		csCenter[0]=y;
		csCenter[0]=z;
		csRadius = r;
	}
	~CollisionBall(){}

	/*
	int isPlayerCollide(PlayerCtrl* p1,PlayerCtrl* enemy){
		return dist(p1->pos,enemy->pos) <= 10;
	}
	*/
	
	GLfloat dist(GLfloat* pos1,GLfloat* pos2){
		//vec len is 3
		return sqrt(
			pow( pos1[0]-pos2[0] ,2)+
			pow( pos1[1]-pos2[1] ,2)+
			pow( pos1[2]-pos2[2] ,2)
		);
	}
};


class TestObject{
public:
	//draw a test object in scene
	TestObject(){}
	~TestObject(){}

	static void drawCube(float x,float y,float z){
		glPushMatrix();
		{
			glTranslatef(x,y,z);
			glutSolidCube(1);
		}
		glPopMatrix();
	}
};