#include<vector>

#include"Snake.h"

using namespace std;
const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600, BODY_WIDTH = 16;

Snake::Snake()
	:dir(Snake::direction::RIGHT)
{
	Body* bodypart = nullptr;
	for (int i = 0; i < 3; ++i)
	{
		bodypart = new Body((SCREEN_WIDTH >> 1) - i * BODY_WIDTH, SCREEN_HEIGHT >> 1);
		body.push_back(bodypart);
	}
}

void Snake::move()
{
	SDL_Rect src, dst;
	for (int i = (int) body.size() - 1; i > 0; --i)
	{
		body[i]->move(body[i]->calDirection(*body[i - 1]));
	}

	body[0]->move(dir);
}

bool Snake::eat(Collision& other)
{
	return body[0]->eat(other);
}

void Snake::grow()
{
	int len = (int) body.size();
	int placement = body[len - 2]->calDirection(*body[len - 1]);

	int _x = body[len - 1]->x, _y = body[len - 1]->y;
	Body* newpart = nullptr;
	switch (placement)
	{
	case direction::LEFT:
		_x -= BODY_WIDTH;
		break;
	case direction::RIGHT:
		_x += BODY_WIDTH;
		break;
	case direction::UP:
		_y -= BODY_WIDTH;
		break;
	case direction::DOWN:
		_y += BODY_WIDTH;
		break;
	}
	newpart = new Body(_x, _y);
	body.push_back(newpart);
}

int Snake::getDirection()
{
	return dir;
}

void Snake::updDirection(int newdir)
{
	if ((dir == Snake::direction::LEFT || dir == Snake::direction::RIGHT) && (newdir == Snake::direction::UP || newdir == Snake::direction::DOWN))
		dir = newdir;
	if((dir == Snake::direction::UP || dir == Snake::direction::DOWN) && (newdir == Snake::direction::LEFT || newdir == Snake::direction::RIGHT))
		dir = newdir;
}

void Snake::renderSnake(RenderWindow& screen)
{
	SDL_Rect src;
	SDL_Rect dst = { body[0]->x, body[0]->y, 16,16 };
	switch (dir)
	{
	case direction::LEFT:
		src = { 48, 0, 16,16 };
		break;
	case direction::RIGHT:
		src = { 16, 0, 16,16 };
		break;
	case direction::UP:
		src = { 0, 0, 16,16 };
		break;
	case direction::DOWN:
		src = { 32, 0, 16,16 };
		break;
	}
	screen.render(src, dst);

	int len = (int) body.size();
	for (int i = 1; i < len - 1; ++i)
	{
		int toNext = body[i]->calDirection(*body[i - 1]);
		int toPre = body[i]->calDirection(*body[i + 1]);
		
		if ((toNext == direction::UP && toPre == direction::LEFT) || (toNext == direction::LEFT && toPre == direction::UP))
			src = { 48, 32, 16, 16 };
		else if ((toNext == direction::UP && toPre == direction::RIGHT) || (toNext == direction::RIGHT && toPre == direction::UP))
			src = { 0, 32, 16, 16 };
		else if ((toNext == direction::DOWN && toPre == direction::LEFT) || (toNext == direction::LEFT && toPre == direction::DOWN))
			src = { 32, 32, 16, 16 };
		else if ((toNext == direction::DOWN && toPre == direction::RIGHT) || (toNext == direction::RIGHT && toPre == direction::DOWN))
			src = { 16, 32, 16, 16 };

		else if (toNext == direction::UP || toNext == direction::DOWN)
			src = { 0, 48, 16, 16 };
		else
			src = { 16, 48, 16, 16 };
		dst = { body[i]->x, body[i]->y, 16, 16 };
		screen.render(src, dst);
	}

	int lastpart = body[len - 1]->calDirection(*body[len - 2]);
	switch (lastpart)
	{
	case direction::LEFT:
		src = { 48, 16, 16,16 };
		break;
	case direction::RIGHT:
		src = { 16, 16, 16,16 };
		break;
	case direction::UP:
		src = { 0, 16, 16,16 };
		break;
	case direction::DOWN:
		src = { 32, 16, 16,16 };
		break;
	}
	dst = { body[len - 1]->x, body[len - 1]->y, 16,16 };
	screen.render(src, dst);
}