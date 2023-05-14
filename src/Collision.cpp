#include"Collision.h"

const int BODY_WIDTH = 16;

Collision::Collision(int _x, int _y)
	:x(_x), y(_y){}

bool Collision::collapsed(Collision& other)
{
	return (x -  BODY_WIDTH < other.x && other.x < x + BODY_WIDTH && y - BODY_WIDTH < other.y && other.y < y + BODY_WIDTH);
}