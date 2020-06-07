#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <vector>

using namespace std;



class Game
{
public:
	Game();
	void Start();
private:

	//Functions
	void Draw();
	void Input();
	void Logic();
	void RandFruitPosition();

	//variables
	bool gameOver;

	//map
	const unsigned int WIDTH = 20;
	const unsigned int HIGHT = 20;

	unsigned int x, y;
	int fruitX, fruitY;

	vector<int> tailX, tailY;
	int nTail;

	int score;

	enum class eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
	eDirection dir;
};

