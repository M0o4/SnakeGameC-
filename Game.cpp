#include "Game.h"

Game::Game()
{
	gameOver = false;

	dir = Game::eDirection::STOP;

	x = WIDTH / 2;
	y = HIGHT / 2;

	tailX.resize(100, 0);
	tailY.resize(100, 0);

	nTail = 0;

	RandFruitPosition();

	score = 0;
}

void Game::Start()
{
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(70);
	}
}

void Game::Draw()
{
	system("cls");

	cout << "Score: " << score << endl;

	for (unsigned int i = 0; i < WIDTH+2; i++)
	{
		cout << "#";
	}
	cout << endl;
	
	for (unsigned int i = 0; i < HIGHT; i++)
	{
		for (unsigned int j = 0; j < WIDTH; j++)
		{
			if (j == 0) {
				cout << "#";
			}

			if (i == y && j == x) {
				cout << "O";
			}
			else if (i == fruitY && j == fruitX) {
				cout << "F";
			}
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}

			if (j == WIDTH-1) {
				cout << "#";
			}
		}
		cout << endl;
	}

	for (unsigned int i = 0; i < WIDTH+2; i++)
	{
		cout << "#";
	}
	cout << endl << endl;
	cout << "Press \'x\' to end the game" << endl;
}

void Game::Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			if (x - 1 != tailX[0] || nTail == 0)
				dir = Game::eDirection::LEFT;
			break;
		case 'd':
			if(x+1 != tailX[0] || nTail == 0)
				dir = Game::eDirection::RIGHT;
			break;
		case 'w':
			if (y - 1 != tailY[0] || nTail == 0)
				dir = Game::eDirection::UP;
			break;
		case 's':
			if (y + 1 != tailY[0] || nTail == 0)
				dir = Game::eDirection::DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Game::Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;

	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];

		tailX[i] = prevX;
		tailY[i] = prevY;

		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case Game::eDirection::LEFT:
		x--;
		break;
	case Game::eDirection::RIGHT:
		x++;
		break;
	case Game::eDirection::UP:
		y--;
		break;
	case Game::eDirection::DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x > WIDTH || x < 0 || y > HIGHT || y < 0) {
		gameOver = true;
	}

	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY) {
		score += 10;
		RandFruitPosition();
		nTail++;
	}
}

void Game::RandFruitPosition()
{
	srand((unsigned int)time(NULL));

	fruitX = rand() % WIDTH;
	fruitY = rand() % HIGHT;
}
