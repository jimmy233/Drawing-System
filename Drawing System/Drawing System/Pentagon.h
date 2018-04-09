#ifndef _PENTA_H_
#define _PENTA_H_
#include "Graphic.h"
#include <iostream>
#include <GL/glut.h>
using namespace std;

class Pentagon :public Graphic
{
public:
	Pentagon(pixelPoint a, pixelPoint b, pixelPoint c, pixelPoint d, pixelPoint e)
	{
		p.push_back(a);
		p.push_back(b);
		p.push_back(c);
		p.push_back(d);
		p.push_back(e);
		strcpy(type, "Pentagon");
	}
	vector<pixelPoint> get_control_point();
	void draw();
	void move(int x, int y);
	void scale(double Sx, double Sy);
	void rotate(double angle);
	void cut(int xmin, int xmax, int ymin, int ymax);
private:
	vector<pixelPoint> p;
};
vector<pixelPoint> Pentagon::get_control_point()
{
	return p;
}
void Pentagon::draw()
{
	point_list.clear();
	PointOfMe temp4 = { p[3].x,p[3].y };
	PointOfMe temp1 = { p[2].x, p[2].y };
	PointOfMe temp2 = { p[0].x, p[0].y };
	PointOfMe temp3 = { p[1].x,p[1].y };
	PointOfMe temp5 = { p[4].x,p[4].y };
	Line line1(temp5, temp2);
	Line line2(temp2, temp3);
	Line line3(temp3, temp1);
	Line line4(temp1, temp4);
	Line line5(temp4, temp5);
	line1.draw(); line2.draw(); line3.draw(); line4.draw(); line5.draw();
	set<pixelPoint> set1 = line1.get_point_list();
	point_list.insert(set1.begin(), set1.end());
	set<pixelPoint> set2 = line2.get_point_list();
	point_list.insert(set2.begin(), set2.end());
	set<pixelPoint> set3 = line3.get_point_list();
	point_list.insert(set3.begin(), set3.end());
	set<pixelPoint> set4 = line4.get_point_list();
	point_list.insert(set4.begin(), set4.end());
	set<pixelPoint> set5 = line5.get_point_list();
	point_list.insert(set5.begin(), set5.end());
	glFlush();
}

void Pentagon::move(int x, int y)
{
	for (int i = 0; i < p.size(); i++)
		p[i] = { p[i].x + x, p[i].y + y };
}
void Pentagon::scale(double Sx, double Sy)
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
void Pentagon::rotate(double angle)
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
void Pentagon::cut(int xmin, int xmax, int ymin, int ymax)
{
	int min_x = p[0].x, max_x = p[0].x, min_y = p[0].y, max_y = p[0].y;
	for (int j = 0; j < p.size(); j++)
	{
		if (p[j].x < min_x)
			min_x = p[j].x;
		if (p[j].x > max_x)
			max_x = p[j].x;
		if (p[j].y < min_y)
			min_y = p[j].y;
		if (p[j].y > max_y)
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
					else//bottom
					{
						y0 = ymin;
						x0 = (y0 - start.y)*(stop.x - start.x) / (stop.y - start.y) + start.x;
					}
					pixelPoint point = { x0, y0 };
					temp.push_back(point);
				}
				temp.push_back(stop);//all inside
			}
			else
			{
				if (flag)
				{
					flag = false;
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
					else//bottom
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