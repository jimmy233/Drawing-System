#pragma once
#ifndef _LINE_H_
#define _LINE_H_

#include "Graphic.h"
#include "Cut.h"
#include <iostream>
#include <GL/glut.h>
using namespace std;

void swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

class Line :public Graphic
{
public:
	Line(PointOfMe a, PointOfMe b)
	{
		begin = a;
		end = b;
		strcpy(type, "Line");
	}
	vector<pixelPoint> get_control_point();
	void draw();
	void move(int x, int y);
	void scale(double Sx, double Sy);
	void rotate(double angle);
	void cut(int xmin, int xmax, int ymin, int ymax);
};
vector<pixelPoint> Line::get_control_point()
{
	pixelPoint temp1 = { begin.x, begin.y };
	pixelPoint temp2 = { end.x, end.y };
	vector<pixelPoint> temp;
	temp.push_back(temp1);
	temp.push_back(temp2);
	return temp;
}
void Line::draw()
{
	point_list.clear();
	int x0 = begin.x, y0 = begin.y;
	int x1 = end.x, y1 = end.y;

	int dx = x1 - x0;
	int dy = y1 - y0;
	int steps;
	float xave, yave, x = x0, y = y0;;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	xave = float(dx) / float(steps);
	yave = float(dy) / float(steps);

	glBegin(GL_POINTS);
	glVertex3f(x0, y0, 0);  //start point                      
	for (int k = 0; k <= steps; ++k)
	{
		pixelPoint temp = { x, y };
		point_list.insert(temp);
		glVertex3f(x, y, 0);
		x += xave;
		y += yave;
	}
	glVertex3f(x1, y1, 0); //end point
	glEnd();
}

void Line::move(int x, int y)
{
	begin = { begin.x + x, begin.y + y };
	end = { end.x + x, end.y + y };
}
void Line::scale(double Sx, double Sy)
{
	PointOfMe middle = { (begin.x + end.x) / 2, (begin.y + end.y) / 2 };
	begin = {int (begin.x*Sx + middle.x*(1 - Sx)), int(begin.y*Sy + middle.y*(1 - Sy)) };
	end = { int(end.x*Sx + middle.x*(1 - Sx)), int(end.y*Sy + middle.y*(1 - Sy)) };
}
void Line::rotate(double angle)
{
	PointOfMe middle = { (begin.x + end.x) / 2, (begin.y + end.y) / 2 };
	int temp_x = middle.x + (begin.x - middle.x)*cos(angle) - (begin.y - middle.y)*sin(angle);
	int temp_y = middle.y + (begin.x - middle.x)*sin(angle) + (begin.y - middle.y)*cos(angle);
	begin = { temp_x, temp_y };
	temp_x = middle.x + (end.x - middle.x)*cos(angle) - (end.y - middle.y)*sin(angle);
	temp_y = middle.y + (end.x - middle.x)*sin(angle) + (end.y - middle.y)*cos(angle);
	end = { temp_x, temp_y };

}
void Line::cut(int xmin, int xmax, int ymin, int ymax)
{
	cutPoint temp= cutLine(xmin, xmax, ymin, ymax, begin.x, begin.y, end.x, end.y);
	if (temp.in_window)
	{
		glColor3f(1.0, 1.0, 1.0);
		draw();
		glFlush();
		PointOfMe p1 = { temp.begin.x,temp.begin.y };
		PointOfMe p2 = { temp.end.x, temp.end.y };
		Line newLine(p1, p2);
		point_list.clear();
		glColor3f(0.0, 0.0, 0.0);
		newLine.draw();
		set<pixelPoint> set = newLine.get_point_list();
		point_list.insert(set.begin(), set.end());
		begin = p1;
		end = p2;
		glFlush();
	}
}
#endif
