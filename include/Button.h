#pragma once

#include<iostream>
#include<SDL.h>
#include<string.h>

#include"RenderWindow.h"

using std::string;

class Button
{
private:
	int x, y;
	SDL_Texture* clickedTex;
	SDL_Texture* defaultTex;
	SDL_Texture* texture;
public:
	Button(int _x, int _y, RenderWindow& screen, string name);
	bool check(int _x, int _y, RenderWindow& screen);
	void renderButton(RenderWindow& screen);
};