#pragma once
#ifndef _3DSHOW_
#define _3DSHOW_

#include "menu.h"

GLfloat AngleX;
GLfloat AngleY;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	{
		glRotatef(AngleX, 1.0f, 0.0f, 0.0f);
		glRotatef(AngleY, 0.0f, 1.0f, 0.0f);

		glBegin(GL_POLYGON); //ǰ����    
		glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);//��ɫ����Ϊ��ɫ    
		glVertex3f(50.0f, 50.0f, 50.0f);

		glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);//��ɫ����Ϊ��ɫ    
		glVertex3f(50.0f, -50.0f, 50.0f);

		glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);//��ɫ����Ϊ��ɫ    
		glVertex3f(-50.0f, -50.0f, 50.0f);

		glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);//��ɫ����Ϊ��ɫ    
		glVertex3f(-50.0f, 50.0f, 50.0f);
		glEnd();

		glBegin(GL_POLYGON); //�����    
		glColor3f(0.0f, 1.0f, 1.0f);//��ɫ����Ϊ��ɫ    
		glVertex3f(50.0f, 50.0f, -50.0f);

		glColor3f(0.0f, 1.0f, 0.0f);//��ɫ����Ϊ��ɫ    
		glVertex3f(50.0f, -50.0f, -50.0f);

		glColor3f(0.0f, 0.0f, 0.0f);//��ɫ����Ϊ��ɫ    
		glVertex3f(-50.0f, -50.0f, -50.0f);

		glColor3f(0.0f, 0.0f, 1.0f);//��ɫ����Ϊ��ɫ    
		glVertex3f(-50.0f, 50.0f, -50.0f);
		glEnd();

		glBegin(GL_POLYGON); //�ϱ���    
		glColor3d(0.0, 1.0, 1.0);//��ɫ����Ϊ��ɫ    
		glVertex3f(50.0f, 50.0f, -50.0f);

		glColor3d(1.0, 1.0, 1.0);//��ɫ����Ϊ��ɫ    
		glVertex3f(50.0f, 50.0f, 50.0f);

		glColor3d(1.0, 0.0, 1.0);//��ɫ����ΪƷ��ɫ    
		glVertex3f(-50.0f, 50.0f, 50.0f);

		glColor3d(0.0, 0.0, 1.0);//��ɫ����Ϊ��ɫ    
		glVertex3f(-50.0f, 50.0f, -50.0f);
		glEnd();

		glBegin(GL_POLYGON); //�±���    
		glColor3ub(0u, 255u, 0u);//��ɫ����Ϊ��ɫ    
		glVertex3f(50.0f, -50.0f, -50.0f);

		glColor3ub(255u, 255u, 0u);//��ɫ����Ϊ��ɫ    
		glVertex3f(50.0f, -50.0f, 50.0f);

		glColor3ub(255u, 0u, 0u);//��ɫ����Ϊ��ɫ    
		glVertex3f(-50.0f, -50.0f, 50.0f);

		glColor3ub(0u, 0u, 0u);//��ɫ����Ϊ��ɫ    
		glVertex3f(-50.0f, -50.0f, -50.0f);
		glEnd();

		glBegin(GL_POLYGON); //�����    
		glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);//��ɫ����Ϊ��ɫ    
		glVertex3f(50.0f, 50.0f, 50.0f);

		glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)255);//��ɫ����Ϊ��ɫ    
		glVertex3f(50.0f, 50.0f, -50.0f);

		glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);//��ɫ����Ϊ��ɫ    
		glVertex3f(50.0f, -50.0f, -50.0f);

		glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);//��ɫ����Ϊ��ɫ    
		glVertex3f(50.0f, -50.0f, 50.0f);
		glEnd();

		glBegin(GL_POLYGON); //�ұ���    
		glColor3f(1.0f, 0.0f, 1.0f);//��ɫ����ΪƷ��ɫ    
		glVertex3f(-50.0f, 50.0f, 50.0f);

		glColor3f(0.0f, 0.0f, 1.0f);//��ɫ����Ϊ��ɫ    
		glVertex3f(-50.0f, 50.0f, -50.0f);

		glColor3f(0.0f, 0.0f, 0.0f);//��ɫ����Ϊ��ɫ    
		glVertex3f(-50.0f, -50.0f, -50.0f);

		glColor3f(1.0f, 0.0f, 0.0f);//��ɫ����Ϊ��ɫ    
		glVertex3f(-50.0f, -50.0f, 50.0f);
		glEnd();
	}
	glPopMatrix();


	glutSwapBuffers();
}

void reshape(int w, int h)
{
	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	GLfloat nRange = 100.0f;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION); //����ǰ����ָ��ΪͶӰģʽ    
	glLoadIdentity();

	//������άͶӰ��    

	if (w <= h)
	{
		glOrtho(-nRange, nRange, -nRange * aspect, nRange * aspect, -nRange, nRange);
	}
	else
	{
		glOrtho(-nRange, nRange, -nRange / aspect, nRange / aspect, -nRange, nRange);
	}
}

void key_board(GLint key, GLint x, GLint y)
{
	if (key == GLUT_KEY_UP)
	{
		AngleX -= 5.0f;
	}
	if (key == GLUT_KEY_DOWN)
	{
		AngleX += 5.0f;
	}
	if (key == GLUT_KEY_LEFT)
	{
		AngleY -= 5.0f;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		AngleY += 5.0f;
	}
	if (AngleX > 355.0f)
	{
		AngleX = 0.0f;
	}
	if (AngleX < 0.0f)
	{
		AngleX = 355.0f;
	}
	if (AngleY > 355.0f)
		AngleY = 0.0f;

	if (AngleY < 0.0f)
	{
		AngleY = 355.0f;
	}
	glutPostRedisplay();
}

void init()
{
	AngleX = 45.0f;
	AngleY = 315.0f;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DITHER);
	glShadeModel(GL_SMOOTH);
}
#endif