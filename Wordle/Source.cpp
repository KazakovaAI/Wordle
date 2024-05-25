#include<iostream>
#include<vector>
#include"glut.h"
void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 690);
	glutCreateWindow("Wordle");
	init();
	//Button_set();
	glutDisplayFunc(display);
	//glutMouseFunc(mouse);
	glutMainLoop();
}