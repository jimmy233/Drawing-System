#pragma once
#ifndef _FILL_H_
#define _FILL_H_
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <stack>
#include "Graphic.h"
#define ERROR -100
using namespace std;
struct Color
{
	float r;
	float g;
	float b;
	bool operator !=(const Color &c) const
	{
		if (abs(r - c.r) < 0.001&&abs(g - c.g) < 0.001&&abs(b - c.b) < 0.001)
			return false;
		else
			return true;
	}
};
Color getPixel(int x, int y)
{
	Color c;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &c);
	return c;
}
void setPixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

//扫描线填充算法
bool NotBorderAndNotFill(int x, int y, Color fillColor, Color borderColor)
{
	Color currentColor = getPixel(x, y);
	if (currentColor != fillColor&&currentColor != borderColor)
		return true;
	else
		return false;
}
bool AlreadyFill(int x, int y, Color fillColor)
{
	Color currentColor = getPixel(x, y);
	if (currentColor != fillColor)
		return false;
	else
		return true;
}
void SearchNewLineSeed(stack<pixelPoint>&stk, int xLeft, int xRight, int y, Color fillColor, Color borderColor)
{
	int x = xLeft;
	while (AlreadyFill(x, y, fillColor))
	{
		x++;
	}
	while (x <= xRight)
	{
		bool findNewSeed = false;
		while (NotBorderAndNotFill(x, y, fillColor, borderColor) && (x < xRight))
		{
			findNewSeed = true;
			x++;
		}
		if (findNewSeed)
		{
			if (NotBorderAndNotFill(x, y, fillColor, borderColor) && (x == xRight))//无边界点
			{
				pixelPoint seed = { x, y };
				stk.push(seed);
				break;
			}
			else
			{
				pixelPoint seed = { x - 1, y };
				stk.push(seed);

				x++;
			}
		}
		else
			x++;
	}
}
int FillLineRight(int x, int y, Color fillColor, Color borderColor)
{
	int count = 0;
	glColor3f(fillColor.r, fillColor.g, fillColor.b);
	while (NotBorderAndNotFill(x, y, fillColor, borderColor))
	{
		setPixel(x, y);
		x++;
		count++;
		if (count >= 500)
			return ERROR;
	}
	return x - 1;
}
int FillLineLeft(int x, int y, Color fillColor, Color borderColor)
{
	int count = 0;
	glColor3f(fillColor.r, fillColor.g, fillColor.b);
	while (NotBorderAndNotFill(x, y, fillColor, borderColor))
	{
		setPixel(x, y);
		x--;
		count++;
		if (count >= 500)
			return ERROR;
	}
	return x + 1;
}
void ScanLineFill(int x, int y, Color fillColor, Color borderColor)
{
	stack<pixelPoint> stk;
	pixelPoint first = { x, y };
	stk.push(first);
	while (!stk.empty())
	{
		pixelPoint seed;
		seed = stk.top();
		stk.pop();

		int xRight = FillLineRight(seed.x, seed.y, fillColor, borderColor);
		if (xRight == ERROR)
		{
			cout << "无法填充" << endl;
			return;
		}
		Color rc = getPixel(xRight, seed.y);
		int xLeft = FillLineLeft(seed.x - 1, seed.y, fillColor, borderColor);
		if (xLeft == ERROR)
		{
			cout << "无法填充" << endl;
			return;
		}
		Color lc = getPixel(xLeft, seed.y);
		SearchNewLineSeed(stk, xLeft, xRight, seed.y + 1, fillColor, borderColor);
		SearchNewLineSeed(stk, xLeft, xRight, seed.y - 1, fillColor, borderColor);
	}
}
#endif