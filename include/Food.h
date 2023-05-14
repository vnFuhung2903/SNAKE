#pragma once

#include"Collision.h"
#include"RenderWindow.h"

class RenderWindow;

struct Food:Collision
{
	Food();
	void renderFood(RenderWindow& screen);
};