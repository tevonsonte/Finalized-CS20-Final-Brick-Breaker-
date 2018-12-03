#include <iostream>
#include <gl/glut.h>
#include <list>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class MainMenu {
public:
	list <string> sb; //list

	MainMenu() { scoreboard(); }
	int display();
	void scoreboard();
	void Draw();
	void Init() { glEnable(GL_LIGHT0); }
private:
	struct listBckgrnd { //background for scoreboard list struct
		int x, y, w, h;
		char *label;
	};

	char lTitle[11] = "Scoreboard"; //set title for pseudo button
	listBckgrnd lbg = { 25, 25, 400, 500, lTitle };
	int choice;
	int counter; //counter for outputting list

	void bkgndDisplay(listBckgrnd *lbg);
	void Draw2D() { bkgndDisplay(&lbg); }
	void Font(void *font, char *text, int x, int y);
};

int MainMenu::display() { //inital menu
	cout << "Welcome to Breakout's Pre-Game Menu\n";
	cout << "__________________________\n";
	cout << "1. Start Program" << endl;
	cout << "2. See Scoreboard" << endl;
	cout << "3. Exit" << endl;

	//get user choice
	cout << "Please enter your selection: ";
	cin >> choice;

	return choice;
}

void MainMenu::scoreboard() {
	string l;
	ifstream board;
	try { //exception handling

		board.open("Scores.txt");

		if (board.is_open()) {
			//clear list on call to prevent duplication of scores
			sb.clear();

			//populate list from scoreboard if it already exists
			while (!board.eof())
			{
				board >> l;
				sb.push_back(l);
			}
		}
	}
	catch (...) {
		cout << "Error opening file\n";
	}

	board.close();
}

void MainMenu::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//2d glut options
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	//setbackground color
	glClearColor(0, 0, 0, 1);

	//set view point
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 600, 600, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Draw2D();

	glutSwapBuffers();
}

void MainMenu::Font(void *font, char *text, int x, int y){
	glRasterPos2i(x, y);

	while (*text != '\0') {
		glutBitmapCharacter(font, *text);
		++text;
	}
}

void MainMenu::bkgndDisplay(listBckgrnd *lbg) {
	int x, y;
	char *entry = NULL;
	if (lbg) {
		glColor3f(1.0f, 0.5f, 0.0f); //orange color

		//draw background for list
		glBegin(GL_QUADS);
		glVertex2i(lbg->x, lbg->y);
		glVertex2i(lbg->x, lbg->y + lbg->h);
		glVertex2i(lbg->x + lbg->w, lbg->y + lbg->h);
		glVertex2i(lbg->x + lbg->w, lbg->y);
		glEnd();

		glLineWidth(5); //outline

		x = lbg->x + (lbg->w - (600 / 2)); //set text to middle of background
		y = 50; //set text to top of background

		//display Header
		for (int i = 0; i < 11; i++) {
			glColor3f(0, 0, 1);
			glRasterPos2i(x, 50);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lTitle[i]);
			x += 15;
		}

		//use list iterator to get score list
		list<string>::iterator itr; //list iterator
		string length;
		for (itr = sb.begin(); itr != sb.end(); itr++) {
			length = *itr;
			x = lbg->x + (lbg->w - (600 / 2)); //reset x coord for output

			for (int i = 0; i < length.length(); i++) {
				glColor3f(1, 1, 1);
				glRasterPos2i(x,y+15);
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, length[i]);
				x += 15; //move output over after every letter
			}
			y += 15; //move text to next line
		}
	}
}