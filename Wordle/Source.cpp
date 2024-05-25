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
	glLineWidth(1);
	glBegin(GL_LINES);
	for (int i = -100; i <= 100; i += 10)
	{
		if (i == 0)
		{
			glColor3f(0.0, 0.0, 1.0);
		}
		else
		{
			glColor3f(0.5, 0.5, 0.3);
		}
		glVertex2f(i, -100);
		glVertex2f(i, 100);
		glVertex2f(-100, i);
		glVertex2f(100, i);
	}
	glEnd();
}
int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(680, 680);
	glutCreateWindow("Wordle");
	init();
	//Button_set();
	glutDisplayFunc(display);
	//glutMouseFunc(mouse);
	glutMainLoop();
}