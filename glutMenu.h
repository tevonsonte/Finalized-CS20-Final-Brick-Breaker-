#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "config.h"
#include <gl/glut.h> //include from file directory

void buttonAction()
{
}

class gMenu {
public:
	int counter = 0; //forces different colors for buttons depending on # of times draw is called
	struct Mouse
	{
		int x;		//	x coordinate of  mouse cursor	
		int y;		//	y coordinate of  mouse cursor	
		int lmb;	// left mouse button tracker	
		int xpress; //	x-coord of first button press 
		int ypress; //	y-coord of first button press 	
	};

	typedef struct Mouse Mouse;

	Mouse mouse = { 0,0,0,0,0 };

	int winw = winWidth; //get window width from config
	int winh = winHeight; //get window height from config

	typedef void(*ButtonCallback)();

	struct Button
	{
		int   x;							// x coord 
		int   y;							// y coord 
		int   w;							// width  
		int   h;							// height
		int	  state;						// 1 if pressed, 0 otherwise 
		int	  highlighted;					// mouse hover
		char *label;						// button title
		ButtonCallback callbackFunction;	// pointer to function call
	};
	typedef struct Button Button;

	char btitle[5] = "Play"; //set button title
	char ttitle[14] = "Breakout Game"; //title button nameplate

	Button playButton = { 50, 450, 300, 75, 0,0, btitle, buttonAction };
	Button titleButton = { 40, 50, 650, 150, 0,0, ttitle, buttonAction };

	void Font(void *font, char *text, int x, int y)
	{
		glRasterPos2i(x, y);

		while (*text != '\0')
		{
			glutBitmapCharacter(font, *text);
			++text;
		}
	}

	int ButtonClickTest(Button* b, int x, int y)
	{
		if (b)
		{
			//checks where mouse click occurs
			if (x > b->x      &&
				x < b->x + b->w &&
				y > b->y      &&
				y < b->y + b->h) {
				return 1;
			}
		}
		return 0;
	}

	void ButtonRelease(Button *b, int x, int y)
	{
		if (b)
		{
			//checks if mouse click and release is on top of button
			if (ButtonClickTest(b, mouse.xpress, mouse.ypress) &&
				ButtonClickTest(b, x, y))
			{
				return;
			}

			//reset button state
			b->state = 0;
		}
	}

	void ButtonPress(Button *b, int x, int y)
	{
		if (b)
		{
			//check if button actually pressed
			if (ButtonClickTest(b, x, y))
			{
				b->state = 1;
			}
		}
	}

	void ButtonPassive(Button *b, int x, int y)
	{
		if (b)
		{
			//check if mouse is hovered over button
			if (ButtonClickTest(b, x, y))
			{
				//highlight when mouse hovers
				if (b->highlighted == 0) {
					b->highlighted = 1;
					glutPostRedisplay();
				}
			}
			else

				// redraw when mouse is absent
				if (b->highlighted == 1)
				{
					b->highlighted = 0;
					glutPostRedisplay();
				}
		}
	}

	void ButtonDraw(Button *b)
	{
		int fontx; //x coord for font
		int fonty; //y coord for font

		if (b)
		{
			//highlights button on mouse hover
			if (b->highlighted)
				glColor3f(0.9f, 0.9f, 0.9f);
			else {
				if(b->label == ttitle) //set specific color for title button
					glColor3f(1.0f, 0.0f, 1.0f); //default color when not highlighted
				else 
					glColor3f(1.0f, 0.5f, 0.0f); //default color of first button created ("play button")
			}

			//button background with cool triangle texture/gradiant thing (black "arrow")
			glBegin(GL_QUADS);
			if (b->label == ttitle) //manual color adjustment
				glColor3f(0.85f, 0.0f, 0.85f);
			else
				glColor3f(0.85f, 0.35f, 0.0f);
			glVertex2i(b->x, b->y);
			glVertex2i(b->x + b->w, b->y + b->h);
			if (b->label == ttitle) //manual colors adjustment
				glColor3f(0.7f, 0.0f, 0.6f);
			else
				glColor3f(0.7f, 0.3f, 0.0f);
			glVertex2i(b->x, b->y + b->h);
			if (b->label == ttitle) //manual colors adjustment
				glColor3f(0.95f, 0.0f, 0.9f);
			else
				glColor3f(0.95f, 0.22f, 0.0f);
			glVertex2i(b->x + b->w, b->y);
			glEnd();

			//outline for button
			glLineWidth(3);

			//reverse outline color on hover
			if (b->state)
				glColor3f(0.4f, 0.4f, 0.4f);
			else
				glColor3f(0.8f, 0.8f, 0.8f);

			glBegin(GL_LINE_STRIP);
			glVertex2i(b->x + b->w, b->y);
			glVertex2i(b->x, b->y);
			glVertex2i(b->x, b->y + b->h);
			glEnd();

			if (b->state)
				glColor3f(0.8f, 0.8f, 0.8f);
			else
				glColor3f(0.4f, 0.4f, 0.4f);

			glBegin(GL_LINE_STRIP);
			glVertex2i(b->x, b->y + b->h);
			glVertex2i(b->x + b->w, b->y + b->h);
			glVertex2i(b->x + b->w, b->y);
			glEnd();

			glLineWidth(1);

			//gets x, y coords for the text string on specific button
			if(b->label == ttitle)
				fontx = b->x + (b->w - (1000 / 2)); // division sets where text sits inside/outside button
			else
				fontx = b->x + (b->w - (400 / 2));
			fonty = b->y + (b->h + 10) / 2;

			//moves button on mouse click to produce the "click" effect
			if (b->state) {
				fontx += 2;
				fonty += 2;
			}

			//fancy stuff when mouse hovers
			//offsets the text and draws a shadow
			if (b->highlighted)
			{
				glColor3f(0, 0, 0);
				if(b->label == ttitle)
					Font(GLUT_BITMAP_TIMES_ROMAN_24, b->label, fontx, fonty);
				else
					Font(GLUT_BITMAP_9_BY_15, b->label, fontx, fonty);
				fontx--;
				fonty--;
			}

			glColor3f(1, 1, 1);
			if (b->label == ttitle)
				Font(GLUT_BITMAP_TIMES_ROMAN_24, b->label, fontx, fonty);
			else
				Font(GLUT_BITMAP_9_BY_15, b->label, fontx, fonty);
		}
	}

	void Init()
	{
		glEnable(GL_LIGHT0);
	}

	void Draw2D()
	{
		ButtonDraw(&playButton);
		ButtonDraw(&titleButton);
	}

	void Draw()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//setbackground color
		glClearColor(0.2, 0.5, 0.9, 1);

		//2d glut options
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);

		//set view point
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 800, 600, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		Draw2D();

		glutSwapBuffers();
	}

	void MouseButton(int button, int state, int x, int y)
	{
		//mouse pos
		mouse.x = x;
		mouse.y = y;

		if (state == GLUT_DOWN)
		{
			//location of moouse click
			if (!(mouse.lmb)) {
				mouse.xpress = x;
				mouse.ypress = y;
			}

			switch (button)
			{
			case GLUT_LEFT_BUTTON:
				mouse.lmb = 1;
				ButtonPress(&playButton, x, y);
			}
		}

		//redraw
		glutPostRedisplay();
	}

	void MouseMotion(int x, int y)
	{
		//calculate mouse movement
		int dx = x - mouse.x;
		int dy = y - mouse.y;

		//mouse pos
		mouse.x = x;
		mouse.y = y;


		//highlight button on mouse hover
		ButtonPassive(&playButton, x, y);

		//redraw
		glutPostRedisplay();
	}

	void MousePassiveMotion(int x, int y)
	{

		//Calculate mouse movement		 
		int dx = x - mouse.x;
		int dy = y - mouse.y;

		mouse.x = x;
		mouse.y = y;

		ButtonPassive(&playButton, x, y);
	}
};