#ifndef game_H
#define game_H

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <gl/glut.h> //include glut header from file directory

//programmer made header files
#include "gObjects.h" // Game objects header
#include "config.h"  // Game configs header
using namespace std;


class Stack { //stack with a struct vector
private:
	int index;
public:
	vector <Ball> balls;
	void push(Ball b); //push element into vector
	void pop(); //pop last pushed element (ball)
	void wipe(); //clear vector
	int peek(); //check number of balls entered by user
};

class Breakout {

public:
	int score; //score

	//Constructor / Destructor
	Breakout();
	~Breakout();

	// Public functions (GLUT calls)
	void display(void);
	void init(void);
	void reshape(int width, int height);
	void mouseClick(int button, int state, int x, int y);
	void mouseMove(int x, int y);
	void keyInput(unsigned char key, int x, int y);
	void specialKeyPos(int key, int x, int y);

private:
	Stack s;
	// Game stats
	int level; //either 1 or 2
	int reward; //reward for completing game/brick breaking , etc. (score boost)
	int lifeCount; //balls / life total

	// game mode state enum for switch case stuff
	enum State { INIT, Menus, Gameplay, Scoreboard };
	
	Breakout::State gameState;

	// Paddle
	Paddle paddle;

	// Bricks
	vector<Brick> bricks;

	// game/object creation functions
	void drawBckgrnd(void);
	void drawGame(void);
	void addBall(float x, float y);
	void drawBalls(void);
	void paddleInit(void);
	void drawPaddle(void);
	void brickInit(void);
	void levelOneBricks(void);
	void levelTwoBricks(void);
	void drawBrick(void);

	template <typename T>
	int wallHit(T it);

	template <typename T>
	bool brickHit(T it, T br);

	template <typename T>
	T hitBrick(T brick);

	void drawLifeTotal(float x, float y);
	void drawStats(void);
	void drawScore(void);
	void drawCoords(void);
};

#endif