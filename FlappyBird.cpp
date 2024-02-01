#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>

const int width = 80;
const int height = 20;
enum Direction { UP, DOWN };
Direction birdDir;
bool gameOver;

int birdX, birdY;
char gameField[height][width];

struct Obstacle
{
	int x;
	int gap;
	int gapHeight;
};

std::vector<Obstacle> obstacles;
int score = 0;
int obstacleAddCounter = 0;

void initGameField()
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (x == 0 || x == width - 1)
			{
				gameField[y][x] = '#';
			}
			else
			{
				gameField[y][x] = ' ';
			}
		}
	}
}

void drawGameField()
{
	system("cls");

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (x == birdX && y == birdY)
			{
				std::cout << "*";
			}
			else
			{
				std::cout << gameField[y][x];
			}
		}
		std::cout << std::endl;
	}
}

void input()
{
	if (_kbhit())
	{
		char pressedKey = _getch();
		if (pressedKey == ' ' || pressedKey == 72)
		{
			birdDir = UP;
		}
	}
}

void updateBird()
{
	if (birdDir == UP)
	{
		birdY--;
		birdDir = DOWN;
	}
	else
	{
		if (birdY < height - 2)
		{
			birdY++;
		}
	}
}

void addObstacle(int x, int gap, int gapHeight)
{
	Obstacle newObstacle = { x, gap, gapHeight };
	obstacles.push_back(newObstacle);
}

void moveObstacles()
{
	for (auto& obs : obstacles)
	{
		obs.x--;
	}

	obstacles.erase
	(
		std::remove_if
		(
			obstacles.begin(),
			obstacles.end(),
			[](const Obstacle& o) {return o.x < 0;}
		),
		obstacles.end()
	);
}

void drawObstacles()
{
	for (auto& obs : obstacles)
	{
		for (int y = 0; y < height; ++y)
		{
			if (y < obs.gap || y > obs.gap + obs.gapHeight)
			{
				gameField[y][obs.x] = '|';
			}
		}
	}
}

void clearObstacles()
{
	for (auto& obs : obstacles)
	{
		for (int y = 0; y < height; ++y)
		{
			if (gameField[y][obs.x] == '|')
			{
				gameField[y][obs.x] = ' ';
			}
		}
	}
}

void checkCollision()
{
	for (auto& obs : obstacles)
	{
		if (birdX == obs.x)
		{
			if (birdY < obs.gap || birdY > obs.x + obs.gapHeight)
			{
				gameOver = true;
				return;
			}
		}
	}
}

void updateScore()
{
	for (auto& obs : obstacles)
	{
		if (obs.x == birdX)
		{
			score++;
		}
	}
}

void showScore()
{
	std::cout << "Score: " << score << std::endl;
}

int main()
{
	birdX = 10;
	birdY = height / 2;
	initGameField();

	addObstacle(width - 20, 10, 5);
	addObstacle(width - 10, 12, 4);

	while (!gameOver)
	{
		if (obstacleAddCounter++ > 15)
		{
			int gap = rand() % (height - 10) + 3;
			addObstacle(width - 1, gap, 5);
			obstacleAddCounter = 0;
		}
		clearObstacles();
		moveObstacles();
		drawObstacles();
		drawGameField();
		input();
		updateBird();
		checkCollision();
		updateScore();
		showScore();
		Sleep(100);
	}
	return 0;
}