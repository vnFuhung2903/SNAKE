#include<iostream>

#include"Food.h"
#include"RenderWindow.h"

const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600, FOOD_WIDTH = 16;

Food::Food():Collision(0, 0)
{
	srand(time(NULL));
	x = rand() % (SCREEN_WIDTH/FOOD_WIDTH) * FOOD_WIDTH;
	y = rand() % (SCREEN_HEIGHT/FOOD_WIDTH) * FOOD_WIDTH;
}

void Food::renderFood(RenderWindow& screen)
{
	SDL_Rect src = { 32, 48, 16, 16 };
	SDL_Rect dst = { x, y, 16, 16 };
	screen.render(src, dst);
}

