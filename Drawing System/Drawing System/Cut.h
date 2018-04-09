#pragma once
#ifndef _CUT_H_
#define _CUT_H_

#include <GL/glut.h>
#include <iostream>
#include "Graphic.h"
using namespace std;

bool cutOrNot(double p, double q, double &u1, double &u2)
{
	bool flag = true;
	double r = q / p;
	if (p < 0)
	{
		if (r > u1)
		{
			u1 = r;
			if (u1 > u2)
				flag = false;
		}

	}
	else if (p > 0)
	{
		if (r < u2)
		{
			u2 = r;
			if (u1 > u2)
				flag = false;
		}
	}
	else
	{
		if (q < 0)
			flag = false;
	}
	return flag;
}

cutPoint cutLine(int xwmin, int xwmax, int ywmin, int ywmax, int x1, int y1, int x2, int y2)
{
	double u1 = 0, u2 = 1;
	double dx = x2 - x1, dy = y2 - y1;

	double p1 = -dx, q1 = x1 - xwmin;
	double p2 = dx, q2 = xwmax - x1;
	double p3 = -dy, q3 = y1 - ywmin;
	double p4 = dy, q4 = ywmax - y1;

	bool in_window = cutOrNot(p1, q1, u1, u2) && cutOrNot(p2, q2, u1, u2) && cutOrNot(p3, q3, u1, u2) && cutOrNot(p4, q4, u1, u2);
	if (in_window)
	{
		if (u2 < 1.0)
		{
			x2 = x1 + u2*dx; 
			y2 = y1 + u2*dy;
		}
		if (u1 > 0.0)
		{
			x1 = x1 + u1*dx; 
			y1 = y1 + u1*dy;
		}
	}
	cutPoint temp;
	temp.in_window = in_window;
	temp.begin = { x1, y1 };
	temp.end = { x2, y2 };
	return temp;
}
#endif