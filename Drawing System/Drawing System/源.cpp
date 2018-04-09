#define _CRT_SECURE_NO_WARNINGS
#include <cmath>
#include <iostream>
#include <GL/glut.h>
#include "menu.h"
#include "MouseClick.h"
using namespace std;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(Length,Width);
	glutCreateWindow("Drawing System");
		init();
		glutDisplayFunc(&display);
	


	int polygon_menu = glutCreateMenu(polygonMenu);
	glutAddMenuEntry("Triangle", 1);
	glutAddMenuEntry("Quadrangle", 2);
	glutAddMenuEntry("Pentagon", 3);
	glutAddMenuEntry("Hexagon", 4);

	int menu_a = glutCreateMenu(drawMenu);

	glutAddSubMenu("Polygon", polygon_menu);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Circle", 3);
	glutAddMenuEntry("Oval", 4);
	glutAddMenuEntry("Rectangle", 5);
	glutAddMenuEntry("Bezier", 6);

	int menu_b = glutCreateMenu(motionMenu);
	glutAddMenuEntry("Translation", 1);
	glutAddMenuEntry("Rotation", 2);
	glutAddMenuEntry("Magnify", 3);
	glutAddMenuEntry("Shrink", 4);

	int menu_c = glutCreateMenu(fillMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);




	glutCreateMenu(mainMenu);   //main_menu
	glutAddSubMenu("Draw", menu_a);
	glutAddSubMenu("Motion", menu_b);
	glutAddSubMenu("Fill", menu_c);
	glutAddMenuEntry("Cut", 4);
	glutAddMenuEntry("Save", 5);
	glutAddMenuEntry("Read", 6);
	glutAddMenuEntry("Clean", 7);
	glutAddMenuEntry("3Dcube Show", 8);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMouseFunc(&myMouse);
	glutMotionFunc(&mouseMotion);
	
	glutMainLoop();
	return 0;
}
