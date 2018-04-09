#pragma once


#ifndef _Graphic_H_
#define _Graphic_H_
#include <iostream>
#include <cmath>
#include <set>
#include <vector>
using namespace std;

struct PointOfMe
{
	int x;
	int y;
	bool invalid;
};

struct pixelPoint//像素点
{
	int x;
	int y;
	bool operator <(const pixelPoint &p) const
	{
		if (x < p.x)
			return true;
		else if (x == p.x)
		{
			if (y < p.y)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	bool operator !=(const pixelPoint &p) const
	{
		if (x == p.x&&y == p.y)
			return false;
		else
			return true;
	}
	bool operator ==(const pixelPoint &p)const
	{
		if (x == p.x&&y == p.y)
			return true;
		else
			return false;
	}
};
struct cutPoint
{
	pixelPoint begin;
	pixelPoint end;
	bool in_window;
};


class Graphic
{
public:
	void putpixel(int xc, int yc, int x, int y);
	virtual void draw() = 0;
	virtual void move(int x, int y) = 0;
	virtual void rotate(double angle) = 0; 
	virtual void scale(double Sx, double Sy) = 0;
	virtual void cut(int xmin, int xmax, int ymin, int ymax) = 0;//裁剪框
	virtual vector<pixelPoint> get_control_point() = 0;
	bool in_border(int x, int y); //判断边界线
	set<pixelPoint> get_point_list();
	char* get_type();
	int getRightOfX();
	int getLeftOfX();
	int getTopOfY();
	int getBottomOfY();
protected:
	PointOfMe begin;
	PointOfMe end;
	char type[20]; //图元类型
	set<pixelPoint> point_list;//绘制点
};
struct Direction
{
	int x_offset;
	int y_offset;
};
Direction direction_8[] = { { -1, 0 },{ -1, 1 },{ 0, 1 },{ 1, 1 },{ 1, 0 },{ 1, -1 },{ 0, -1 },{ -1, -1 } };
bool IfInWindowOrnot(pixelPoint border_begin, pixelPoint border_end, pixelPoint p)
{
	int v = (border_end.x - border_begin.x)*(p.y - border_begin.y) - (p.x - border_begin.x)*(border_end.y - border_begin.y);
	if (v <= 0)
		return true;
	else
		return false;
}

set<pixelPoint> Graphic::get_point_list()
{
	return point_list;
}
bool Graphic::in_border(int x, int y)
{
	bool in = false;
	for (int i = 0; i < 8; i++)
	{
		pixelPoint temp = { x + direction_8[i].x_offset, y + direction_8[i].y_offset };
		set<pixelPoint>::iterator it = point_list.find(temp);
		if (it != point_list.end())
		{
			in = true;
			break;
		}
	}
	return in;
}
char* Graphic::get_type()
{
	return type;
}
int Graphic::getRightOfX()
{
	if (begin.x > end.x)
		return begin.x;
	else
		return end.x;
}
int Graphic::getLeftOfX()
{
	if (begin.x < end.x)
		return begin.x;
	else
		return end.x;
}
int Graphic::getTopOfY()
{
	if (begin.y > end.y)
		return begin.y;
	else
		return end.y;
}
int Graphic::getBottomOfY()
{
	if (begin.y < end.y)
		return begin.y;
	else
		return end.y;
}



vector<Graphic*> Graphic_list;//存储每一个图形
#endif