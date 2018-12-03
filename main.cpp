//Class Structures/Concepts used: 
//Classes, vectors, exception handling, lists, templates, stack

#include <iostream>
#include <assert.h>
#include "math.h"
#include <gl/glut.h> //include from file directory
#include "game.h"
#include "consoleStuff.h"
#include "menu.h"
#include <Windows.h>
using namespace std;

MainMenu m;

void mdisplay() {
	m.Draw();
}

// main
int main(int argc, char ** argv)
{

	int user = m.display(); //call menu

	switch (user) {
	case 1: { //start game case

		// Init for glut
		glutInit(&argc, argv);

		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
		// display Init

		//set up game window
		glutInitWindowSize(winWidth, winHeight);
		glutInitWindowPosition(100, 100);
		glutCreateWindow(argv[0]); //create menu window
		glutSetWindowTitle("BrickBreaker Menu");
		g.Init();
		glutDisplayFunc(gDraw);
		glutMouseFunc(gMouseButton);
		glutPassiveMotionFunc(gMousePassiveMotion);

		
		Sleep(500); //slow down loading so game doesnt start before player is ready
		glutInitWindowPosition(100, 100);
		glutCreateWindow(title); //create game window

		// game init
		game.init();

		// display game
		glutDisplayFunc(myDisplay);
		// call reshape function
		glutReshapeFunc(redraw);
		// call mouse click event
		glutMouseFunc(mouseClick);

		// track mouse motion function call
		glutPassiveMotionFunc(mouseMovement);
		// grab keyboard input
		glutKeyboardFunc(keyPress);
		// identify special key inputs
		glutSpecialFunc(specialKeyPress);
		// opengl loop
		glutMainLoop();

	} break;
	case 2: { //scoreboard case
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);

		glutInitWindowPosition(100,100);
		glutInitWindowSize(600, 600);
		glutCreateWindow(argv[0]); //create Scoreboard window
		glutSetWindowTitle("Scoreboard");
		m.Init();
		glutDisplayFunc(mdisplay);

		glutMainLoop();
	}break;
	case 3: //exit case
		return 0;
	}


	system("pause");
	return 0;
} // end main