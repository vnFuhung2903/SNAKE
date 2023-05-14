#pragma once

#include "Collision.h"

struct Body:Collision
{
	Body();
	Body(int _x, int _y);
	void move(int dir);
	int calDirection(Body& other);
};