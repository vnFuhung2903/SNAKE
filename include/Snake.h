#pragma once

#include<vector>

#include"Body.h"
#include"RenderWindow.h"

using std::vector;

class RenderWindow;

class Snake
{
private:
	int dir;

public:
	Snake();
	vector<Body* > body;
	enum direction
	{
		UP, DOWN, LEFT, RIGHT
	};
	int getDirection();
	void updDirection(int newdir);
	void move();
	void grow();
	bool eat(Collision &other);
	void renderSnake(RenderWindow& screen);
};