#pragma once
#ifndef _BEZIER_H_
#define _BEZIER_H_

#include "Graphic.h"
#include "Line.h"
#include <iostream>
#include <GL/glut.h>
#define NUM 4//控制点个数

using namespace std;

class Bezier :public Graphic
{
public:
	Bezier(pixelPoint temp[], int n)
	{
		for (int i = 0; i < n; i++)
			p[i] = temp[i];
		strcpy(type, "Bezier");
	}
	vector<pixelPoint> get_control_point();
	void draw();
	void draw_control_border();
	void move(int x, int y);
	void scale(double Sx, double Sy);
	void rotate(double angle);
	void cut(int xmin, int xmax, int ymin, int ymax) {}
private:
	pixelPoint p[NUM];
	pixelPoint	bz[11];
};
vector<pixelPoint> Bezier::get_control_point()
{
	vector<pixelPoint> temp;
	for (int i = 0; i < NUM; i++)
		temp.push_back(p[i]);
	return temp;
}
void Bezier::draw_control_border()
{
	for (int i = 0; i < NUM - 1; i++)
	{
		PointOfMe begin = { p[i].x, p[i].y };
		PointOfMe end = { p[i + 1].x, p[i + 1].y };
		Line line(begin, end);
		line.draw();
	}
}
void Bezier::draw()
{
	point_list.clear();
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < NUM; i++)
	{
		pixelPoint temp;
		temp = { p[i].x,p[i].y };
		point_list.insert(temp);
		glVertex2i(p[i].x, p[i].y);
	}
	glEnd();
	int n = NUM;
	float a0, a1, a2, a3, b0, b1, b2, b3;
	a0 = p[0].x;
	a1 = -3 * p[0].x + 3 * p[1].x;
	a2 = 3 * p[0].x - 6 * p[1].x + 3 * p[2].x;
	a3 = -p[0].x + 3 * p[1].x - 3 * p[2].x + p[3].x;
	b0 = p[0].y;
	b1 = -3 * p[0].y + 3 * p[1].y;
	b2 = 3 * p[0].y - 6 * p[1].y + 3 * p[2].y;
	b3 = -p[0].y + 3 * p[1].y - 3 * p[2].y + p[3].y;
	float t = 0;
	float dt = 0.01;
	for (int i = 0; t < 1.1; t += 0.1, i++)
	{
		bz[i].x = a0 + a1*t + a2*t*t + a3*t*t*t;
		bz[i].y = b0 + b1*t + b2*t*t + b3*t*t*t;
	}
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 11; i++)
	{
		pixelPoint temp;
		temp = { p[i].x,p[i].y };
		point_list.insert(temp);
		glVertex2i(bz[i].x, bz[i].y);
	}
	glEnd();
	glFlush();
	
}
void Bezier::move(int x, int y)
{
	for (int i = 0; i < NUM; i++)
		p[i] = { p[i].x + x, p[i].y + y };
}
void Bezier::scale(double Sx, double Sy)
{
	int total_x = 0, total_y = 0;
	for (int i = 0; i < NUM; i++)
	{
		total_x += p[i].x;
		total_y += p[i].y;
	}
	pixelPoint middle = { total_x / NUM, total_y / NUM };
	for (int i = 0; i < NUM; i++)
		p[i] = { int(p[i].x*Sx + middle.x*(1 - Sx)), int(p[i].y*Sy + middle.y*(1 - Sy)) };
}
void Bezier::rotate(double angle)
{
	int total_x = 0, total_y = 0;
	for (int i = 0; i < NUM; i++)
	{
		total_x += p[i].x;
		total_y += p[i].y;
	}
	pixelPoint middle = { total_x / NUM, total_y / NUM };
	for (int i = 0; i < NUM; i++)
	{
		int temp_x = middle.x + (p[i].x - middle.x)*cos(angle) - (p[i].y - middle.y)*sin(angle);
		int temp_y = middle.y + (p[i].x - middle.x)*sin(angle) + (p[i].y - middle.y)*cos(angle);
		p[i] = { temp_x, temp_y };
	}
}
#endif