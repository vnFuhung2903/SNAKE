#pragma once

#include<iostream>
#include<Windows.h>
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
	bool collapsed(Collision &other);
	void renderSnake(RenderWindow& screen);
};