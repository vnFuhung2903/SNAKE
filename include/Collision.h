#pragma once

struct Collision
{
	int x, y;
	Collision(int _x, int _y);
	bool collapsed(Collision& other);
};