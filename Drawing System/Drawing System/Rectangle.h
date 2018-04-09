#pragma once
#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "Graphic.h"
#include "Line.h"
#include <iostream>
#include <GL/glut.h>
using namespace std;

class Rectangle :public Graphic
{
public:
	Rectangle(PointOfMe a, PointOfMe b)
	{
		pixelPoint temp = { a.x,a.y };
		p.push_back(temp);
		temp = { b.x, a.y };
		p.push_back(temp);
		temp = { b.x, b.y };
		p.push_back(temp);
		temp = { a.x, b.y };
		p.push_back(temp);

		begin = a;
		end = b;
		strcpy(type, "Rectangle");
	}
	vector<pixelPoint> get_control_point();
	void draw();
	void move(int x, int y);
	void scale(double Sx, double Sy);
	void rotate(double angle);
	void cut(int xmin, int xmax, int ymin, int ymax);
private:
	vector<pixelPoint> p; //¿ØÖÆµã
};
vector<pixelPoint> Rectangle::get_control_point()
{
	pixelPoint temp1 = { begin.x, begin.y };
	pixelPoint temp2 = { end.x, end.y };
	vector<pixelPoint> temp;
	temp.push_back(temp1);
	temp.push_back(temp2);
	return temp;
}
void Rectangle::draw()
{
	point_list.clear();

	int i = 0;
	for (; i < p.size() - 1; i++)
	{
		PointOfMe temp1 = { p[i].x, p[i].y };
		PointOfMe temp2 = { p[i + 1].x, p[i + 1].y };
		Line line(temp1, temp2);
		line.draw();
		set<pixelPoint> set = line.get_point_list();
		point_list.insert(set.begin(), set.end());
	}
	PointOfMe temp1 = { p[i].x, p[i].y };
	PointOfMe temp2 = { p[0].x, p[0].y };
	Line line(temp1, temp2);
	line.draw();
	set<pixelPoint> set = line.get_point_list();
	point_list.insert(set.begin(), set.end());

	glFlush();
}
void Rectangle::move(int x, int y)
{
	for (int i = 0; i < p.size(); i++)
		p[i] = { p[i].x + x, p[i].y + y };
}
void Rectangle::scale(double Sx, double Sy)
{

	int temp_x = 0, temp_y = 0;
	int n = p.size();
	for (int i = 0; i < n; i++)
	{
		temp_x += p[i].x;
		temp_y += p[i].y;
	}
	PointOfMe middle = { temp_x / n, temp_y / n };
	for (int i = 0; i < n; i++)
		p[i] = { int(p[i].x*Sx + middle.x*(1 - Sx)), int(p[i].y*Sy + middle.y*(1 - Sy)) };
}
void Rectangle::rotate(double angle)
{

	int temp_x = 0, temp_y = 0;
	int n = p.size();
	for (int i = 0; i < n; i++)
	{
		temp_x += p[i].x;
		temp_y += p[i].y;
	}
	PointOfMe middle = { temp_x / n, temp_y / n };
	for (int i = 0; i < n; i++)
	{
		temp_x = middle.x + (p[i].x - middle.x)*cos(angle) - (p[i].y - middle.y)*sin(angle);
		temp_y = middle.y + (p[i].x - middle.x)*sin(angle) + (p[i].y - middle.y)*cos(angle);
		p[i] = { temp_x, temp_y };
	}
}

void Rectangle::cut(int xmin, int xmax, int ymin, int ymax)
{
	int min_x = p[0].x, max_x = p[0].x, min_y = p[0].y, max_y = p[0].y;
	for (int j = 0; j < p.size(); j++)
	{
		if (p[j].x < min_x)
			min_x = p[j].x;
		if (p[j].x>max_x)
			max_x = p[j].x;
		if (p[j].y < min_y)
			min_y = p[j].y;
		if (p[j].y>max_y)
			max_y = p[j].y;
	}
	bool window_y_in_figure = (min_y <= ymin&&ymin <= max_y) || (min_y <= ymax&&ymax <= max_y);
	bool window_x_in_figure = (min_x <= xmin&&xmin <= max_x) || (min_x <= xmax&&xmax <= max_x);
	bool figure_y_in_window = (ymin <= min_y&&min_y <= ymax) || (ymin <= max_y&&max_y <= ymax);
	bool figure_x_in_window = (xmin < min_x&&min_x <= xmax) || (xmin < max_x&&max_x <= xmax);
	bool y_has_inter = window_y_in_figure | figure_y_in_window;
	bool x_has_inter = window_x_in_figure | figure_x_in_window;
	bool has_inter = x_has_inter & y_has_inter;
	if (!has_inter)
		return;


	glColor3f(1.0, 1.0, 1.0);
	draw();
	point_list.clear();

	vector<pixelPoint> cut;
	pixelPoint t = { xmin, ymax };
	cut.push_back(t);
	t = { xmax, ymax };
	cut.push_back(t);
	t = { xmax, ymin };
	cut.push_back(t);
	t = { xmin, ymin };
	cut.push_back(t);

	pixelPoint start, stop;
	pixelPoint sp, ep;
	bool flag = false;
	int cut_num = cut.size(), n = p.size();
	vector<pixelPoint> temp;

	sp = cut[cut_num - 1];
	for (int i = 0; i < cut_num; i++)
	{
		ep = cut[i];

		start = p[n - 1];
		flag = IfInWindowOrnot(sp, ep, start);
		for (int j = 0; j < n; j++)
		{
			stop = p[j];
			if (IfInWindowOrnot(sp, ep, stop)) 
			{
				if (!flag)
				{
					flag = true;
					int x0, y0;
					if (i == 0)//left
					{
						x0 = xmin;
						y0 = (stop.y - start.y)*(x0 - start.x) / (stop.x - start.x) + start.y;

					}
					else if (i == 1)//top
					{
						y0 = ymax;
						x0 = (y0 - start.y)*(stop.x - start.x) / (stop.y - start.y) + start.x;
					}
					else if (i == 2)//right
					{
						x0 = xmax;
						y0 = (stop.y - start.y)*(x0 - start.x) / (stop.x - start.x) + start.y;
					}
					else
					{
						y0 = ymin;
						x0 = (y0 - start.y)*(stop.x - start.x) / (stop.y - start.y) + start.x;
					}
					pixelPoint point = { x0, y0 };
					temp.push_back(point);
				}
				temp.push_back(stop);
			}
			else
			{
				if (flag)
				{
					flag = false;
					int x0, y0;
					if (i == 0)
					{
						x0 = xmin;
						y0 = (stop.y - start.y)*(x0 - start.x) / (stop.x - start.x) + start.y;

					}
					else if (i == 1)
					{
						y0 = ymax;
						x0 = (y0 - start.y)*(stop.x - start.x) / (stop.y - start.y) + start.x;
					}
					else if (i == 2)
					{
						x0 = xmax;
						y0 = (stop.y - start.y)*(x0 - start.x) / (stop.x - start.x) + start.y;
					}
					else
					{
						y0 = ymin;
						x0 = (y0 - start.y)*(stop.x - start.x) / (stop.y - start.y) + start.x;
					}
					pixelPoint point = { x0, y0 };
					temp.push_back(point);
				}
			}
			start = stop;
		}
		sp = ep;
		p.clear();
		p.insert(p.begin(), temp.begin(), temp.end());
		n = p.size();
		temp.clear();
	}


	glColor3f(0.0, 0.0, 0.0);
	int i = 0;
	for (i = 0; i < p.size() - 1; i++)
	{
		PointOfMe p1 = { p[i].x, p[i].y };
		PointOfMe p2 = { p[i + 1].x, p[i + 1].y };
		Line newLine(p1, p2);
		glColor3f(0.0, 0.0, 0.0);
		newLine.draw();
		set<pixelPoint> set = newLine.get_point_list();
		point_list.insert(set.begin(), set.end());
	}
	PointOfMe p1 = { p[i].x, p[i].y };
	PointOfMe p2 = { p[0].x, p[0].y };
	Line newLine(p1, p2);
	glColor3f(0.0, 0.0, 0.0);
	newLine.draw();
	set<pixelPoint> set = newLine.get_point_list();
	point_list.insert(set.begin(), set.end());
	glFlush();
}
#endif