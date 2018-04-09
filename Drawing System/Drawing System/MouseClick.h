#pragma once
#ifndef _MOUSECLICK_H_
#define _MOUSECLICK_H_

#include "Graphic.h"
#include "Line.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Oval.h"
#include "Fill.h"
#include "Triangle.h"
#include "Quadrilatera.h"
#include "Pentagon.h"
#include "Bezier.h"
#include "Hexagonh.h"
#include "menu.h"

#define SHRINK 0.75 //缩小系数
#define ENLARGE 1.25 //放大系数
#define ANGLE 30 //旋转度数
#define j2h(x) (3.1415926*(x)/180.0) 

Graphic *figure;
Graphic *cut_window;

int moveBegin_x, moveEnd_x = 0, moveBegin_y, moveEnd_y = 0;
int before_x = 0, after_x = 0, before_y = 0, after_y = 0;

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN&&p_begin.invalid)
		{
			p_begin.x = x;
			p_begin.y = Width - y;
			Color black = { 0.0, 0.0, 0.0 };
			if (ArrayBool[13])//R
			{
				Color red = { 1.0, 0.0, 0.0 };
				ScanLineFill(p_begin.x, p_begin.y, red, black);
				glFlush();
			}
			if (ArrayBool[14])//G
			{
				Color green = { 0.0, 1.0, 0.0 };
				ScanLineFill(p_begin.x, p_begin.y, green, black);
				glFlush();
			}
			if (ArrayBool[15])//B
			{
				Color blue = { 0.0, 0.0, 1.0 };
				ScanLineFill(p_begin.x, p_begin.y, blue, black);
				glFlush();
			}

			if (ArrayBool[4])//triangle
			{
				glBegin(GL_POINTS);
				glVertex2i(p_begin.x, p_begin.y);
				glEnd();
				glFlush();
				triangle_point[triangle++] = { p_begin.x, p_begin.y };
				if (triangle == 3)
				{
					figure = new Triangle(triangle_point[0], triangle_point[1], triangle_point[2]);
					glColor3f(0.0, 0.0, 0.0);
					figure->draw();
					Graphic_list.push_back(figure);
					triangle= 0;
				}
			}
			if (ArrayBool[5])//quadri
			{
				glBegin(GL_POINTS);
				glVertex2i(p_begin.x, p_begin.y);
				glEnd();
				glFlush();
				quadrilateral_point[quadri++] = { p_begin.x, p_begin.y };
				if (quadri == 4)
				{
					figure = new Quadrilateral(quadrilateral_point[0], quadrilateral_point[1], quadrilateral_point[2], quadrilateral_point[3]);
					glColor3f(0.0, 0.0, 0.0);
					figure->draw();
					Graphic_list.push_back(figure);
					quadri = 0;
				}
			}
			if (ArrayBool[6])//pentagon
			{
				glBegin(GL_POINTS);
				glVertex2i(p_begin.x, p_begin.y);
				glEnd();
				glFlush();
				pentagon_point[pentagon++] = { p_begin.x, p_begin.y };
				if (pentagon== 5)
				{
					figure = new Pentagon(pentagon_point[0], pentagon_point[1], pentagon_point[2], pentagon_point[3], pentagon_point[4]);
					glColor3f(0.0, 0.0, 0.0);
					figure->draw();
					Graphic_list.push_back(figure);
					pentagon = 0;
				}
			}
			if (ArrayBool[16])
			{
				glBegin(GL_POINTS);
				glVertex2i(p_begin.x, p_begin.y);
				glEnd();
				glFlush();
				hexagon_point[hexagon++] = { p_begin.x, p_begin.y };
				if (hexagon == 6)
				{
					figure = new Hexagon(hexagon_point[0], hexagon_point[1], hexagon_point[2], hexagon_point[3], hexagon_point[4],hexagon_point[5]);
					glColor3f(0.0, 0.0, 0.0);
					figure->draw();
					Graphic_list.push_back(figure);
					hexagon = 0;
				}
			}
			if (ArrayBool[7])
			{
				glBegin(GL_POINTS);
				glVertex2i(p_begin.x, p_begin.y);
				glEnd();
				glFlush();
				
				bezier_points[bezier] = { p_begin.x, p_begin.y };
				bezier++;
				if (bezier == NUM)
				{
					figure = new Bezier(bezier_points, NUM);
					glColor3f(0.0, 0.0, 0.0);
					figure->draw();
					Graphic_list.push_back(figure);
					bezier= 0;
				}
			}

			if (ArrayBool[10] || ArrayBool[11] || ArrayBool[12])
			{
				int i;
				for (i = 0; i < Graphic_list.size(); i++)
				{
					if (Graphic_list[i]->in_border(p_begin.x, p_begin.y))
						break;
				}
				if (i != Graphic_list.size())
				{
					glColor3f(1.0, 1.0, 1.0);
					Graphic_list[i]->draw();
					if (ArrayBool[12])
						Graphic_list[i]->scale(SHRINK, SHRINK);
					else if (ArrayBool[11])
						Graphic_list[i]->scale(ENLARGE, ENLARGE);
					else
						Graphic_list[i]->rotate(j2h(ANGLE));
					glColor3f(0.0, 0.0, 0.0);
					Graphic_list[i]->draw();
					for (int j = 0; j < Graphic_list.size(); j++)
						Graphic_list[j]->draw();
					glFlush();
				}

			}
			figure = NULL;
		}
		if (state == GLUT_UP&&p_end.invalid)
		{
			if (figure != NULL)
			{
				Graphic_list.push_back(figure);
				figure = NULL;
			}
			if (cut_window != NULL&&ArrayBool[8])
			{
				glColor3f(1.0, 1.0, 1.0);
				cut_window->draw();
				for (int i = 0; i < Graphic_list.size(); i++)
					Graphic_list[i]->cut(cut_window->getLeftOfX(), cut_window->getRightOfX(), cut_window->getBottomOfY(), cut_window->getTopOfY());

				glFlush();
			}		
			p_end.invalid = false;
		}
		if (state == GLUT_UP)
		{
			after_x = after_y = 0;
		}
	}

}
void mouseMotion(int x, int y)
{
	PointOfMe before = p_end;
	p_end.x = x;
	p_end.y = Width - y;

	if (ArrayBool[0]&&p_end.invalid)
	{
		glColor3f(1.0, 1.0, 1.0);
		figure = new Line(p_begin, before);
		figure->draw();

		glColor3f(0.0, 0.0, 0.0);
		figure = new Line(p_begin, p_end);
		figure->draw();

		for (int i = 0; i < Graphic_list.size(); i++)
			Graphic_list[i]->draw();
		glFlush();
	}
	if (ArrayBool[3]&&p_end.invalid)
	{
		glColor3f(1.0, 1.0, 1.0);
		figure = new Rectangle(p_begin, before);
		figure->draw();

		glColor3f(0.0, 0.0, 0.0);
		figure = new Rectangle(p_begin, p_end);
		figure->draw();

		for (int i = 0; i < Graphic_list.size(); i++)
			Graphic_list[i]->draw();
		glFlush();
	}
	if (ArrayBool[8]&&p_end.invalid&&p_begin.invalid)
	{
		if (cut_window != NULL)
		{
			glColor3f(1.0, 1.0, 1.0);
			cut_window->draw();
		}
			glColor3f(1.0, 1.0, 1.0);
			cut_window = new Rectangle(p_begin, before);
			cut_window->draw();

			glColor3f(.0, 0.0, 1.0);
			cut_window = new Rectangle(p_begin, p_end);
			cut_window->draw();

			cut_window->draw();
		glColor3f(0.0, 0.0, 0.0);
		for (int i = 0; i < Graphic_list.size(); i++)
			Graphic_list[i]->draw();
		glFlush();
	}
	if (ArrayBool[1]&&p_end.invalid)
	{
		glColor3f(1.0, 1.0, 1.0);
		figure = new Circle(p_begin, before);
		figure->draw();

		glColor3f(0.0, 0.0, 0.0);
		figure = new Circle(p_begin, p_end);
		figure->draw();

		for (int i = 0; i <Graphic_list.size(); i++)
			Graphic_list[i]->draw();
		glFlush();
	}
	if (ArrayBool[2]&&p_end.invalid)
	{
		glColor3f(1.0, 1.0, 1.0);
		figure = new Oval(p_begin, before);
		figure->draw();

		glColor3f(0.0, 0.0, 0.0);
		figure = new Oval(p_begin, p_end);
		figure->draw();

		for (int i = 0; i < Graphic_list.size(); i++)
			Graphic_list[i]->draw();
		glFlush();
	}

	if (ArrayBool[9]&&p_end.invalid)
	{
		int i;
		for (i = 0; i < Graphic_list.size(); i++)
		{
			if (Graphic_list[i]->in_border(p_begin.x + after_x, p_begin.y + after_y))

			{
				moveBegin_x = p_begin.x;
				moveBegin_y = p_begin.y;
				moveEnd_x = p_end.x;
				moveEnd_y = p_end.y;
				break;
			}
		}
		if (i != Graphic_list.size())
		{
			before_x = after_x;
			after_x = moveEnd_x - moveBegin_x;
			before_y = after_y;
			after_y = moveEnd_y - moveBegin_y;

			glColor3f(1.0, 1.0, 1.0);
			Graphic_list[i]->draw();
			glColor3f(0.0, 0.0, 0.0);

			Graphic_list[i]->move(after_x - before_x, after_y - before_y);
			Graphic_list[i]->draw();

			for (int j = 0; j < Graphic_list.size(); j++)
				Graphic_list[j]->draw();
			glFlush();
		}
	}
	moveBegin_x = moveBegin_y = moveEnd_x = moveEnd_y = 0;
	p_end.invalid = true;
}

#endif