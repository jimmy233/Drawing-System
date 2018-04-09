#pragma once
#ifndef _MENU_H_
#define _MENU_H_

#include <GL/glut.h>
#include "Graphic.h"
#include "Cut.h"
#include "Bezier.h"
#include "File.h"
#include <iostream>
#include <vector>
using namespace std;


#define Length 600
#define Width 600

static PointOfMe p_begin;
static PointOfMe p_end;


bool ArrayBool[17] = { false };

//line 0 circle 1 oval 2 rectangle 3 triangle 4 qua 5 pentagon 6 bezier 7 cut 8 trans 9 rotate 10 manify 11 shrink 12 r 13
//g 14 b 15 hexagon 16
pixelPoint triangle_point[3], quadrilateral_point[4], pentagon_point[5],hexagon_point[6], bezier_points[NUM];
int triangle = 0, quadri = 0, pentagon = 0, hexagon=0, bezier = 0;
bool cutR = true, cutC = false;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

}
void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
							
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, Length, 0, Width);
}
void polygonMenu(int value)
{
	triangle = 0, quadri = 0, pentagon = 0, bezier = 0; hexagon = 0;
	cutR = true, cutC = false;
	for (int i = 0; i < 17; i++)
	{
		ArrayBool[i] = false;
	}
	p_begin.invalid = true;
	switch (value)
	{
	case 1:
		ArrayBool[4] = true;
		break;
	case 2:
		ArrayBool[5] = true;
		break;
	case 3:
		ArrayBool[6] = true;
		break;
	case 4:
		ArrayBool[16] = true;
		break;
	}
}
void drawMenu(int value)
{
	cutR = true, cutC = false;
	for (int i = 0; i < 17; i++)
	{
		ArrayBool[i] = false;
	}
	triangle = 0, quadri = 0, pentagon = 0, bezier = 0; hexagon = 0;
	p_begin.invalid = true;
	switch (value)
	{
	case 2:
		 ArrayBool[0]= true;
		break;
	case 3:
		ArrayBool[1] = true;
		break;
	case 4:
		ArrayBool[2] = true;
		break;
	case 5:
		ArrayBool[3] = true;
		break;
	case 6:
		ArrayBool[7] = true;
		break;
	case 1:
		break;
	}
}
void motionMenu(int value)
{
	cutR = true, cutC = false;
	for (int i = 0; i < 16; i++)
	{
		ArrayBool[i] = false;
	}
	triangle = 0, quadri = 0, pentagon = 0, bezier = 0; hexagon = 0;
	switch (value)
	{
	case 1:
		ArrayBool[9] = true;
		break;
	case 2:
		ArrayBool[10] = true;
		break;
	case 3:
		ArrayBool[11] = true;
		break;
	case 4:
		ArrayBool[12] = true;
		break;
	}
}
void fillMenu(int value)
{
	cutR = true, cutC = false;
	for (int i = 0; i < 17; i++)
	{
		ArrayBool[i] = false;
	}
	triangle = 0, quadri = 0, pentagon = 0, bezier = 0; hexagon = 0;
	switch (value)
	{
	case 1:
		ArrayBool[13] = true;
		break;
	case 2:
		ArrayBool[14] = true;
		break;
	case 3:
		ArrayBool[15] = true;
		break;
	}
}
void mainMenu(int value)
{
	switch (value)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		for (int i = 0; i < 17; i++)
		{
			ArrayBool[i] = false;
		}
		triangle = 0, quadri = 0, pentagon = 0, bezier = 0; hexagon = 0;
		cutR = true, cutC = false;
		ArrayBool[8] = true;
		break;
	case 5:
		save();
		break;
	case 6:
		Read();
		p_begin.invalid = true;
		break;
	case 7:
		for (int i = 0; i < 17; i++)
		{
			ArrayBool[i] = false;
		}
		triangle = 0, quadri = 0, pentagon = 0, bezier = 0; hexagon = 0;
		cutR = true, cutC = false;
		p_end.invalid = false;
		glClear(GL_COLOR_BUFFER_BIT);
		Graphic_list.clear();
		glFlush();
		break;
	case 8:
		break;
	}
}

#endif