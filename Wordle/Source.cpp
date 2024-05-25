#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include"glut.h"
using std::string;
using std::vector;

void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500, 500, -350, 350);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(1);
	glBegin(GL_LINES);
	for (int i = -1000; i <= 1000; i += 25)
	{
		if (i == 0)
		{
			glColor3f(0.0, 0.0, 1.0);
		}
		else
		{
			glColor3f(0.5, 0.5, 0.3);
		}
		glVertex2f(i, -350);
		glVertex2f(i, 350);
		if (abs(i) <= 350)
		{
			glVertex2f(-500, i);
			glVertex2f(500, i);
		}
	}
	glEnd();
	glutSwapBuffers();
}

struct Window {
	static string current;
};
string Window::current = "Main menu";

struct Point
{
	double x = 0;
	double y = 0;
	Point(double x1, double y1)
	{
		x = x1;
		y = y1;
	}
	Point(const Point& p)
	{
		x = p.x;
		y = p.y;
	}
	Point() = default;
	Point& operator=(const Point& P)
	{
		x = P.x;
		y = P.y;
		return *this;
	}
	/*Point& operator+=(const Point& P)
	{
		x += P.x;
		y += P.y;
		return *this;
	}
	Point& operator-=(const Point& P)
	{
		x -= P.x;
		y -= P.y;
		return *this;
	}
	Point& operator*=(const double& k)
	{
		x *= k;
		y *= k;
		return *this;
	}*/
	/*Point rotate(double angle, Point center)
	{
		double pi = 3.14159265;
		angle *= pi;
		angle /= 180;
		Point p1(x, y);
		p1 -= center;
		Point res;
		res.x = p1.x * cos(angle) - p1.y * sin(angle);
		res.y = p1.x * sin(angle) + p1.y * cos(angle);
		res += center;
		return res;
	}*/
	void draw(vector <double> colors = { 0, 0, 0 }, double size = 5) const
	{
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glColor3f(colors[0], colors[1], colors[2]);
		glVertex2d(x, y);
		glEnd();
		glFlush();
	}
};

class Button
{
private:
	double x = 0;
	double y = 0;
	double width = 0;
	double height = 0;
	const char* text = nullptr;
public:
	vector <double> color = { 0.2, 0.2, 0.7 };
	Button() = default;
	Button(double x, double y, double width, double height, const char* text) : x(x), y(y), width(width), height(height), text(text) {}
	void change(const double& xi, const double& yi, const double& h, const double& w, const char* s)
	{
		x = xi;
		y = yi;
		height = h;
		width = w;
		text = s;
	}
	void setColor(double first, double second, double third) {
		color[0] = first;
		color[1] = second;
		color[2] = third;
	}
	void drawButton(vector<double> col = { 0.2, 0.4, 0.2 }, vector<double> text_color = { 1.0, 1.0, 1.0 })
	{
		glBegin(GL_POLYGON);
		glColor3f(col[0], col[1], col[2]);
		glVertex2f(x, y);
		glVertex2f(x + width, y);
		glVertex2f(x + width, y + height);
		glVertex2f(x, y + height);
		glEnd();
		glColor3f(text_color[0], text_color[1], text_color[2]);
		int size = strlen(text);
		float textX = x + 1;
		float textY = y + 2;
		glRasterPos2f(textX, textY);
		for (int i = 0; i < size; i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		}
		glFlush();
		//glutSwapBuffers();
	}
	bool isPressed(const Point& pr) const
	{
		if (pr.x < x)
		{
			return false;
		}
		if (pr.x > x + width)
		{
			return false;
		}
		if (pr.y < y)
		{
			return false;
		}
		if (pr.y > y + height)
		{
			return false;
		}
		return true;
	}

};

class Buttons
{
public:
	static Button quit;
	static Button let4;
	static Button let5;
	static Button let6;
	/*static Button rotate;
	static Button reflex_point;
	static Button reflex_line;*/
	static vector<Button> keyboard;
};

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 700);
	glutCreateWindow("Wordle");
	init();
	//Button_set();
	glutDisplayFunc(display);
	//glutMouseFunc(mouse);
	glutMainLoop();
}