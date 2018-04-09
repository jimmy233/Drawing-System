#pragma once
#ifndef _OVAL_H_
#define _OVAL_H_
#define _CRT_SECURE_NO_WARNINGS
#include "Graphic.h"

#include <iostream>
#include <GL/glut.h>
using namespace std;


class Oval :public Graphic
{
public:
	Oval(PointOfMe a, PointOfMe b)
	{
		begin = a;
		end = b;
		strcpy(type, "Oval");
	}
	vector<pixelPoint> get_control_point();
	void draw();
	void putpixel(int xc, int yc, int x, int y);
	void move(int x, int y);
	void scale(double Sx, double Sy);
	void rotate(double angle);
	void cut(int xmin, int xmax, int ymin, int ymax) {}
};
vector<pixelPoint> Oval::get_control_point()
{
	pixelPoint temp1 = { begin.x, begin.y };
	pixelPoint temp2 = { end.x, end.y };
	vector<pixelPoint> temp;
	temp.push_back(temp1);
	temp.push_back(temp2);
	return temp;
}
void Oval::draw()
{
	point_list.clear();
	int xc = (begin.x + end.x) / 2;
	int yc = (begin.y + end.y) / 2;

	int a = abs(begin.x - end.x) / 2;
	int b = abs(begin.y - end.y);
	int x, y;  int d1, d2;
	x = 0;  y = b;
	d1 = b*b - a*a*b + 0.25*a*a + 0.5;

	int px = 0;
	int py = 2 * a*a*y;

	putpixel(xc, yc, x, y);
	putpixel(xc, yc, -x, y);
	putpixel(xc, yc, -x, -y);
	putpixel(xc, yc, x, -y);
	while (py > px)//(2*b*b*(x) < 2*a*a*(y) )
	{
		x++;
		px = px + 2 * b*b;
		if (d1 < 0)
		{
			d1 += b*b + px;
		}
		else
		{
			py -= 2 * a*a;
			d1 += b*b + px - py;
			y--;
		}
		putpixel(xc, yc, x, y);
		putpixel(xc, yc, -x, y);
		putpixel(xc, yc, -x, -y);
		putpixel(xc, yc, x, -y);
	}
	d2 = b*b*(x + 0.5)*(x + 0.5) + a*a*(y - 1)*(y - 1) - a*a*b*b + 0.5;
	while (y > 0)
	{
		y--;
		py = py - a*a;
		if (d2 <= 0)
		{
			px = px + 2 * b*b;
			d2 += a*a - py + px;
			x++;
		}
		else
		{
			d2 += a*a - py;
		}
		putpixel(xc, yc, x, y);
		putpixel(xc, yc, -x, y);
		putpixel(xc, yc, -x, -y);
		putpixel(xc, yc, x, -y);
	}

	
}
void Oval::putpixel(int xc, int yc, int x, int y)
{
	pixelPoint temp;
	glBegin(GL_POINTS);
	temp = { x + xc, y + yc };
	point_list.insert(temp);
	glVertex3f(xc + x, yc + y, 0);
	glEnd();
}
void Oval::move(int x, int y)
{
	begin = { begin.x + x, begin.y + y };
	end = { end.x + x, end.y + y };

}
void Oval::scale(double Sx, double Sy)
{
	PointOfMe middle = { (begin.x + end.x) / 2, (begin.y + end.y) / 2 };
	begin = { int(begin.x*Sx + middle.x*(1 - Sx)), int(begin.y*Sy + middle.y*(1 - Sy)) };
	end = { int(end.x*Sx + middle.x*(1 - Sx)), int(end.y*Sy + middle.y*(1 - Sy)) };

}
void Oval::rotate(double angle)
{

}
#endif