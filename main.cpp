#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>

#include"include/RenderWindow.h"
#include"include/Food.h"
#include"include/Snake.h"
#include"include/Button.h"

using namespace std;

const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600, BUTTON_WIDTH = 100, BUTTON_HEIGHT = 80;
bool isStarted, isPaused, isRunning, isOver;
RenderWindow screen;

bool holdGame(RenderWindow& screen, int milis)
{
	int startTime = SDL_GetTicks();
	bool runGame = true;
	SDL_Event e;
	while (SDL_GetTicks() - startTime < milis && runGame)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				runGame = false;
				break;
			}
		}
	}
	return runGame;
}

bool pauseGame(RenderWindow& screen)
{
	int startTime = SDL_GetTicks();
	bool runGame = true;
	SDL_Event e;
	while (isPaused && runGame)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				runGame = false;
				break;
			}
			if (e.type == SDL_KEYDOWN)
			{
				isPaused = false;
				break;
			}
		}
	}
	return runGame;
}

void process()
{
	screen.loadImage("SnakeFlip.png");
	Food currentFood = Food();
	Snake snake = Snake();
	isStarted = true, isPaused = false, isRunning = true, isOver = false;
	
	int score = 0, speedlv = 20;
	SDL_Event e;
	while (isRunning)
	{
		screen.clearRenderer();
		currentFood.renderFood(screen);
		snake.renderSnake(screen);
		screen.updScoreBoard(score);
		screen.renderSign();
		screen.display();

		if (isStarted)
		{
			isRunning = holdGame(screen, 1500);
			isStarted = false;
		}
		if (isPaused)
		{
			isRunning = pauseGame(screen);
			continue;
		}

		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				isRunning = false;
				isOver = true;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					snake.updDirection(Snake::direction::UP);
					break;
				case SDLK_DOWN:
					snake.updDirection(Snake::direction::DOWN);
					break;
				case SDLK_LEFT:
					snake.updDirection(Snake::direction::LEFT);
					break;
				case SDLK_RIGHT:
					snake.updDirection(Snake::direction::RIGHT);
					break;
				case SDLK_w:
					snake.updDirection(Snake::direction::UP);
					break;
				case SDLK_s:
					snake.updDirection(Snake::direction::DOWN);
					break;
				case SDLK_a:
					snake.updDirection(Snake::direction::LEFT);
					break;
				case SDLK_d:
					snake.updDirection(Snake::direction::RIGHT);
					break;
				case SDLK_ESCAPE:
					isPaused = 1;
					break;
				}
				break;
			}
		}

		int timelapse = SDL_GetTicks();
		if (timelapse % speedlv == 0)
		{
			snake.move();
			if (snake.collapsed(currentFood))
			{
				//SDL_Log("eaten");
				currentFood = Food();
				snake.grow();
				++score;
				if (score % 15 == 0 && speedlv > 1)
					--speedlv;
			}

			for (int i = 1; i < (int)snake.body.size(); ++i)
				if (snake.collapsed(*snake.body[i]))
				{
					isOver = true;
				}

			if (isOver)
			{
				isRunning = false;
				break;
			}
		}
	}
}

bool start()
{
	Button startButton = Button((SCREEN_WIDTH >> 1) - 50, 200, screen, "START");
	Button quitButton = Button((SCREEN_WIDTH >> 1) - 50, 300, screen, "QUIT");
	screen.subscreen("WELCOME TO MY SNAKE GAME!");

	SDL_Event e;
	while (true)
	{
		int _x, _y;
		SDL_GetMouseState(&_x, &_y);

		screen.clearRenderer();
		screen.renderSubscreen();
		screen.renderSign();
		startButton.renderButton(screen);
		quitButton.renderButton(screen);
		screen.display();
		while (SDL_PollEvent(&e)) 
		{
			if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONUP)
			{
				if (startButton.check(_x, _y, screen) && e.button.button == SDL_BUTTON_LEFT)
					return 1;
				if (quitButton.check(_x, _y, screen) && e.button.button == SDL_BUTTON_LEFT)
					return 0;
			}
		}
	}
}

bool gameOver()
{
	Button againButton = Button((SCREEN_WIDTH >> 1) - 50, 200, screen, "AGAIN");
	Button quitButton = Button((SCREEN_WIDTH >> 1) - 50, 300, screen, "QUIT");
	screen.subscreen("GAME OVERRR!!!");

	SDL_Event e;
	while (true)
	{
		int _x, _y;
		SDL_GetMouseState(&_x, &_y);

		screen.clearRenderer();
		screen.renderSubscreen();
		screen.renderSign();
		againButton.renderButton(screen);
		quitButton.renderButton(screen);
		screen.display();
		while (SDL_PollEvent(&e)) 
		{
			if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONUP)
			{
				if (againButton.check(_x, _y, screen) && e.button.button == SDL_BUTTON_LEFT)
					return 0;
				if (quitButton.check(_x, _y, screen) && e.button.button == SDL_BUTTON_LEFT)
					return 1;
			}
		}
	}
}

int main(int argc, char* argv[])
{
	screen.sign();
	if (start())
	{
		process();
		while (!gameOver())
			process();
	}
	screen.destroy();
	TTF_Quit();
	SDL_Quit();
	return 0;
}