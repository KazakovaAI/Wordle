#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include"glut.h"
#include<fstream>
using std::string;
using std::vector;
using std::cout;

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

void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500, 500, -350, 350);
	glMatrixMode(GL_MODELVIEW);
}

struct Window {
	static string current;
	static int size;
};
string Window::current = "Main menu";
int Window::size = 0;

class Button
{
private:
	double x = 0;
	double y = 0;
	double width = 0;
	double height = 0;
	string text = " ";
public:
	vector <double> color = { 0.2, 0.2, 0.7 };
	Button() = default;
	Button(double x, double y, double width, double height, string text) : x(x), y(y), width(width), height(height), text(text) {}
	void change(const double& xi, const double& yi, const double& h, const double& w, string s)
	{
		x = xi;
		y = yi;
		height = h;
		width = w;
		text = s;
	}
	void change_text(string s)
	{
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
		int size = text.size();
		float textX = x;
		if (text == "QUIT")
		{
			textX += 45;
		}
		else if (size == 1)
		{
			textX += 19;
		}
		float textY = (2 * y + height) / 2 - 9;
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
	static vector<Button> fields;
	static vector<Button> keyboard;
};
Button Buttons::quit;
Button Buttons::let4;
Button Buttons::let5;
Button Buttons::let6;
vector<Button> Buttons::keyboard(26);
vector<Button> Buttons::fields(36);

class Input {
public:
	static vector<vector<char>> Current_letters;
	static int words_inputed;
	static vector<vector<int>> Right;
	static vector<char> keyboard_place;
	static vector<int> Mark;
};
vector<vector<char>> Input::Current_letters(6);
vector<vector<int>> Input::Right(6);
int Input::words_inputed = 0;
vector<char> Input::keyboard_place = { 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M' };
vector<int> Input::Mark(26);

void DrawKeyboard(int num)
{
	if (Input::Mark[num] == 0)
	{
		Buttons::keyboard[num].setColor(1.0, 1.0, 0.95);
	}
	else if (Input::Mark[num] == 1)
	{
		Buttons::keyboard[num].setColor(0.6, 0.6, 0.6);
	}
	else if (Input::Mark[num] == 2)
	{
		Buttons::keyboard[num].setColor(1.0, 1.0, 0.0);
	}
	else
	{
		Buttons::keyboard[num].setColor(0.0, 1.0, 0.0);
	}
	Buttons::keyboard[num].drawButton(Buttons::keyboard[num].color, {0.0, 0.0, 0.0});
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	int x = -378;
	int y = -120;
	if (num >= 10 && num < 19)
	{
		x = -378 + 34.5;
		y = -120 - 67;
		num %= 10;
	}
	else if (num >= 19)
	{
		x = -378 + 34.5 + 67;
		y = -120 - 67 - 67;
		num %= 19;
	}
	glVertex2f(x + num * 50 + num * 17, y);
	glVertex2f(x + num * 50 + num * 17, y + 50);
	glVertex2f(x + num * 50 + num * 17, y + 50);
	glVertex2f(x + num * 50 + num * 17 + 50, y + 50);
	glVertex2f(x + num * 50 + num * 17 + 50, y + 50);
	glVertex2f(x + num * 50 + num * 17 + 50, y);
	glVertex2f(x + num * 50 + num * 17 + 50, y);
	glVertex2f(x + num * 50 + num * 17, y);
	glEnd();
	glFlush();
}

void DrawFields(int num)
{
	if (Input::Current_letters[num / Window::size].size() > num % Window::size)
	{
		char ch = Input::Current_letters[num / Window::size][num % Window::size];
		string s = "";
		s += ch;
		Buttons::fields[num].change_text(s);
		if (Input::Right[num / Window::size][num % Window::size] == 0)
		{
			Buttons::fields[num].setColor(1.0, 1.0, 0.95);
		}
		else if (Input::Right[num / Window::size][num % Window::size] == 1)
		{
			Buttons::fields[num].setColor(1.0, 1.0, 0);
		}
		else if (Input::Right[num / Window::size][num % Window::size] == 2)
		{
			Buttons::fields[num].setColor(0.0, 1.0, 0);
		}
	}
	else
	{
		Buttons::fields[num].setColor(1.0, 1.0, 0.95);
	}
	Buttons::fields[num].drawButton(Buttons::fields[num].color, { 0.0, 0.0, 0.0 });
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	int x = -150;
	int y = 250;
	if (Window::size == 4)
	{
		x = -100;
	}
	else if (Window::size == 5)
	{
		x = -125;
	}
	int i = num / Window::size;
	int j = num % Window::size;
	glVertex2f(x + j * 50, y - i * 50);
	glVertex2f(x + j * 50, y - i * 50 + 50);
	glVertex2f(x + j * 50, y - i * 50 + 50);
	glVertex2f(x + j * 50 + 50, y - i * 50 + 50);
	glVertex2f(x + j * 50 + 50, y - i * 50 + 50);
	glVertex2f(x + j * 50 + 50, y - i * 50);
	glVertex2f(x + j * 50 + 50, y - i * 50);
	glVertex2f(x + j * 50, y - i * 50);
	glEnd();
	glFlush();
}

void Button_set()
{
	Buttons::quit.change(-70, -250, 50, 140, "QUIT");
	Buttons::let4.change(-300, 175, 50, 140, "4 letters");
	Buttons::let5.change(-70, 175, 50, 140, "5 letters");
	Buttons::let6.change(160, 175, 50, 140, "6 letters");
	int x = -150;
	int y = 250;
	if (Window::size == 4)
	{
		x = -100;
	}
	else if (Window::size == 5)
	{
		x = -125;
	}
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < Window::size; ++j)
		{
			Buttons::fields[i * Window::size + j].change(x + j * 50, y - i * 50, 50, 50, " ");
		}
	}
	x = -378;
	y = -120;
	for (int i = 0; i < 26; ++i)
	{
		int d = i;
		if (i >= 10 && i < 19)
		{
			x = -378 + 34.5;
			y = -120 - 67;
			d %= 10;
		}
		else if (i >= 19)
		{
			x = -378 + 34.5 + 67;
			y = -120 - 67 - 67;
			d %= 19;
		}
		string s = "";
		s += Input::keyboard_place[i];
		Buttons::keyboard[i].change(x + d * 50 + d * 17, y, 50, 50, s);
	}
}

class collection
{
public:
	static vector<string> words4;
	static vector<string> words5;
	static vector<string> words6;
	static int word4_size;
	static int word5_size;
	static int word6_size;
};
int collection::word4_size = 857;
int collection::word5_size = 1594;
int collection::word6_size = 1760;
vector<string> collection::words4;
vector<string> collection::words5;
vector<string> collection::words6;

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
	if (Window::current == "Main menu")
	{
		Buttons::quit.drawButton({ 1.0, 0.0, 0.0 });
		Buttons::let4.drawButton({ 0.0, 1.0, 0.0 });
		Buttons::let5.drawButton({ 0.0, 1.0, 0.0 });
		Buttons::let6.drawButton({ 0.0, 1.0, 0.0 });
	}
	else if (Window::current == "Play")
	{
		for (int i = 0; i < Window::size * 6; ++i)
		{
			DrawFields(i);
		}
		for (int i = 0; i < 26; ++i)
		{
			DrawKeyboard(i);
		}
	}
	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
	double x0 = x - 500;
	double y0 = -y + 350;
	Point p(x0, y0);
	display();
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (Buttons::quit.isPressed(p))
		{
			exit(0);
		}
		else
		{
			if (Buttons::let4.isPressed(p))
			{
				Window::current = "Play";
				Window::size = 4;
				Button_set();
			}
			else if (Buttons::let5.isPressed(p))
			{
				Window::current = "Play";
				Window::size = 5;
				Button_set();
			}
			else if (Buttons::let6.isPressed(p))
			{
				Window::current = "Play";
				Window::size = 6;
				Button_set();
			}
		}
	}
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
	std::ifstream in("4 letters.txt");
	string s;
	for (int i = 0; i < collection::word4_size; ++i)
	{
		in >> s;
		collection::words4.push_back(s);
	}
	in.close();
	in.open("5 letters.txt");
	for (int i = 0; i < collection::word5_size; ++i)
	{
		in >> s;
		collection::words5.push_back(s);
	}
	in.close();
	in.open("6 letters.txt");
	for (int i = 0; i < collection::word6_size; ++i)
	{
		in >> s;
		collection::words6.push_back(s);
	}
	in.close();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 700);
	glutCreateWindow("Wordle");
	init();
	Button_set();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMainLoop();
}