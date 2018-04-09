#pragma once
#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Graphic.h"

#include <iostream>
#include <cmath>
#include <GL/glut.h>
using namespace std;


class Circle :public Graphic
{
public:
	Circle(PointOfMe a, PointOfMe b)
	{
		begin = a;
		end = b;
		strcpy(type, "Circle");
	}
	vector<pixelPoint> get_control_point();
	void draw();
	void move(int x, int y);
	void scale(double Sx, double Sy);
	void rotate(double angle);
	void cut(int xmin, int xmax, int ymin, int ymax) {}
};
vector<pixelPoint> Circle::get_control_point()
{
	pixelPoint temp1 = { begin.x,begin.y };
	pixelPoint temp2 = { end.x, end.y };
	vector<pixelPoint> temp;
	temp.push_back(temp1);
	temp.push_back(temp2);
	return temp;
}
void Circle::draw()
{
	int cx = (begin.x + end.x) / 2;
	int cy = (begin.y + end.y) / 2;
	int r = sqrt((begin.x - end.x)*(begin.x - end.x) + (begin.y - end.y)*(begin.y - end.y)+0.5) / 2;
	point_list.clear();
	int x = 0, y = r;
	float d = 1.25 - r;
	pixelPoint temp;
	while (x <= y) {
		glBegin(GL_POINTS);
		temp = { cx+x, cy + y };
		point_list.insert(temp);
		glVertex2i(cx + x, cy + y);
		temp = { cx - x, cy + y };
		point_list.insert(temp);
		glVertex2i(cx - x, cy + y);

		temp = { cx - x, cy + y };
		point_list.insert(temp);
		glVertex2i(cx - x, cy - y);

		temp = { cx + x, cy - y };
		point_list.insert(temp);
		glVertex2i(cx + x, cy - y);

		temp = { cx + y, cy + x };
		point_list.insert(temp);
		glVertex2i(cx + y, cy + x);

		temp = { cx - y, cy + x };
		point_list.insert(temp);
		glVertex2i(cx - y, cy + x);

		temp = { cx - y, cy - x };
		point_list.insert(temp);
		glVertex2i(cx - y, cy - x);

		temp = { cx + y, cy - x };
		point_list.insert(temp);
		glVertex2i(cx + y, cy - x);
		glEnd();
		if (d < 0) {
			x++;
			d = d + (2 * x + 3);
		}
		else {
			d = d + 2 * x - 2 * y + 5;
			x++;
			y--;
		}
	}
	glFlush();
	
}

void Circle::move(int x, int y)
{
	begin = { begin.x + x, begin.y + y };
	end = { end.x + x, end.y + y };
}
void Circle::scale(double Sx, double Sy)
{
	PointOfMe middle = { (begin.x + end.x) / 2, (begin.y + end.y) / 2 };
	begin = { int(begin.x*Sx + middle.x*(1 - Sx)),int( begin.y*Sy + middle.y*(1 - Sy)) };
	end = { int(end.x*Sx + middle.x*(1 - Sx)), int(end.y*Sy + middle.y*(1 - Sy)) };
}
void Circle::rotate(double angle)
{
	PointOfMe middle = { (begin.x + end.x) / 2, (begin.y + end.y) / 2 };
	int temp_x = middle.x + (begin.x - middle.x)*cos(angle) - (begin.y - middle.y)*sin(angle);
	int temp_y = middle.y + (begin.x - middle.x)*sin(angle) + (begin.y - middle.y)*cos(angle);
	begin = { temp_x, temp_y };
	temp_x = middle.x + (end.x - middle.x)*cos(angle) - (end.y - middle.y)*sin(angle);
	temp_y = middle.y + (end.x - middle.x)*sin(angle) + (end.y - middle.y)*cos(angle);
	end = { temp_x, temp_y };
}
#endif