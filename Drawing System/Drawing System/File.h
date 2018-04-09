#pragma once
#ifndef _FILE_H_
#define _FILE_H_

#include "Graphic.h"
#include "Line.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Oval.h"
#include "Triangle.h"
#include "Quadrilatera.h"
#include "Hexagonh.h"
#include "Pentagon.h"
#include "Bezier.h"
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#define LEN 100
pixelPoint read_x_y(string str)
{
	int pos = str.find(",");
	string p1 = str.substr(0, pos);
	string p2 = str.substr(pos + 1, str.size());
	int x, y;
	stringstream ss1, ss2;
	ss1 << p1;
	ss1 >> x;
	ss2 << p2;
	ss2 >> y;
	pixelPoint point = { x,y };
	return point;
}
void save()
{
	if (Graphic_list.size() == 0)
	{
		cout << "无图形可存储" << endl;
		return;
	}
	char filename[LEN];
	ofstream out;
	cout << "输入文件名（路径+名字）：" << endl;
	cin >> filename;
	out.open(filename, ios::out);
	while (!out.is_open())
	{
		cout << "文件不存在或打开失败，重新输入" << endl;
		cin >> filename;
		out.open(filename, ios::out);
	}
	for (int i = 0; i < Graphic_list.size(); i++)
	{
		char temp[LEN];
		strcpy(temp, Graphic_list[i]->get_type());
		out << temp << " ";
		vector<pixelPoint> point = Graphic_list[i]->get_control_point();
		for (int j = 0; j < point.size(); j++)
			out << point[j].x << "," << point[j].y << " ";
		out << endl;
	}
	cout << "成功保存"<<endl;
	out.close();
}
void Read()
{
	char filename[LEN];
	ifstream in;
	cout << "请输入要读入的文件：" << endl;
	cin >> filename;
	in.open(filename, ios::in);
	while (!in.is_open())
	{
		cout << "文件" << filename << "打开失败，请重新输入：" << endl;
		cin >> filename;
		in.open(filename, ios::in);
	}
	char buffer[LEN];
	while (!in.eof())
	{
		in.getline(buffer, LEN);
		if (strlen(buffer) != 0)
		{
			char *p = strtok(buffer, " ");
			if (strcmp(p, "Bezier") == 0)
			{
				p = strtok(NULL, " ");
				pixelPoint temp[NUM];
				int i = 0;
				while (p != NULL)
				{
					string s = p;
					temp[i++] = read_x_y(s);
					p = strtok(NULL, " ");
				}
				Graphic *graphic = new Bezier(temp, NUM);
				Graphic_list.push_back(graphic);
			}
			
			else if (strcmp(p, "Circle") == 0)
			{
				p = strtok(NULL, " ");
			 PointOfMe temp[2];
				int i = 0;
				while (p != NULL)
				{
					string s = p;
					pixelPoint point = read_x_y(s);
					temp[i++] = { point.x, point.y };
					p = strtok(NULL, " ");
				}
				Graphic *graphic = new Circle(temp[0], temp[1]);
				Graphic_list.push_back(graphic);
			}
			else if (strcmp(p, "Line") == 0)
			{
				p = strtok(NULL, " ");
				PointOfMe temp[2];
				int i = 0;
				while (p != NULL)
				{
					string s = p;
					pixelPoint point = read_x_y(s);
					p = strtok(NULL, " ");
				}
				Graphic *graphic = new Line(temp[0], temp[1]);
				Graphic_list.push_back(graphic);
			}
			else if (strcmp(p, "Oval") == 0)
			{
				p = strtok(NULL, " ");
				PointOfMe temp[2];
				int i = 0;
				while (p != NULL)
				{
					string s = p;
					pixelPoint point = read_x_y(s);
					temp[i++] = { point.x, point.y };
					p = strtok(NULL, " ");
				}
				Graphic *graphic = new Oval(temp[0], temp[1]);
				Graphic_list.push_back(graphic);
			}
			else if (strcmp(p, "Pentagon") == 0)
			{
				p = strtok(NULL, " ");
				pixelPoint temp[5];
				int i = 0;
				while (p != NULL)
				{
					string s = p;
					temp[i++] = read_x_y(s);
					p = strtok(NULL, " ");
				}
				Graphic *graphic = new Pentagon(temp[0], temp[1], temp[2], temp[3], temp[4]);
				Graphic_list.push_back(graphic);
			}
			else if (strcmp(p, "Hexagon") == 0)
			{
				p = strtok(NULL, " ");
				pixelPoint temp[6];
				int i = 0;
				while (p != NULL)
				{
					string s = p;
					temp[i++] = read_x_y(s);
					p = strtok(NULL, " ");
				}
				Graphic *graphic = new Hexagon(temp[0], temp[1], temp[2], temp[3],temp[4],temp[5]);
				Graphic_list.push_back(graphic);
			}
			else if (strcmp(p, "Quadrilateral") == 0)
			{
				p = strtok(NULL, " ");
				pixelPoint temp[4];
				int i = 0;
				while (p != NULL)
				{
					string s = p;
					temp[i++] = read_x_y(s);
					p = strtok(NULL, " ");
				}
				Graphic *graphic = new Quadrilateral(temp[0], temp[1], temp[2], temp[3]);
				Graphic_list.push_back(graphic);
			}
			else if (strcmp(p, "Rectangle") == 0)
			{
				p = strtok(NULL, " ");
				PointOfMe temp[2];
				int i = 0;
				while (p != NULL)
				{
					string s = p;
					pixelPoint point = read_x_y(s);
					temp[i++] = { point.x, point.y };
					p = strtok(NULL, " ");
				}
				Graphic *graphic = new Rectangle(temp[0], temp[1]);
				Graphic_list.push_back(graphic);
			}
			else
			{
				p = strtok(NULL, " ");
				pixelPoint temp[3];
				int i = 0;
				while (p != NULL)
				{
					string s = p;
					temp[i++] = read_x_y(s);
					p = strtok(NULL, " ");
				}
				Graphic *graphic = new Triangle(temp[0], temp[1], temp[2]);
				Graphic_list.push_back(graphic);
			}
		}
	}
	glColor3f(0.0, 0.0, 0.0);
	for (int i = 0; i < Graphic_list.size(); i++)
		Graphic_list[i]->draw();
	glFlush();
	cout << "成功导入" << endl;
	in.close();
}
#endif