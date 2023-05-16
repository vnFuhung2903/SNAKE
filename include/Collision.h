#pragma once

struct Collision
{
	int x, y;
	Collision(int _x, int _y);
	bool eat(Collision& other);
};