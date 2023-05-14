#include<iostream>

#include "Body.h"
#include "Snake.h"

const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600, BODY_WIDTH = 16;

Body::Body(): Collision(0, 0) {}
Body::Body(int _x, int _y): Collision(_x, _y){}

void Body::move(int dir)
{
	switch (dir)
	{
	case Snake::direction::LEFT:
		x -= BODY_WIDTH;
		break;
	case Snake::direction::RIGHT:
		x += BODY_WIDTH;
		break;
	case Snake::direction::UP:
		y -= BODY_WIDTH;
		break;
	case Snake::direction::DOWN:
		y += BODY_WIDTH;
		break;
	}

	if (x > SCREEN_WIDTH - BODY_WIDTH) x = 0;
	if (y > SCREEN_HEIGHT - BODY_WIDTH) y = 0;
	if (x < 0) x = SCREEN_WIDTH - BODY_WIDTH;
	if (y < 0) y = SCREEN_HEIGHT - BODY_WIDTH;
}

int Body::calDirection(Body& other)
{
	if (x == other.x)
	{
		if (y < other.y && abs(y - other.y) <= BODY_WIDTH)
			return Snake::direction::DOWN;
		if (y > other.y && abs(y - other.y) <= BODY_WIDTH)
			return Snake::direction::UP;
		if (y > other.y && abs(y - other.y) > BODY_WIDTH)
			return Snake::direction::DOWN;
		if (y < other.y && abs(y - other.y) > BODY_WIDTH)
			return Snake::direction::UP;
	}
	else if(y == other.y)
	{
		if (x < other.x && abs(x - other.x) <= BODY_WIDTH)
			return Snake::direction::RIGHT;
		if (x > other.x && abs(x - other.x) <= BODY_WIDTH)
			return Snake::direction::LEFT;
		if (x > other.x && abs(x - other.x) > BODY_WIDTH)
			return Snake::direction::RIGHT;
		if (x < other.x && abs(x - other.x) > BODY_WIDTH)
			return Snake::direction::LEFT;
	}
}