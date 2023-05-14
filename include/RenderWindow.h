#pragma once

#include<iostream>
#include<SDL.h>
#include<string.h>

#include"Food.h"
#include"Snake.h"

using std::string;

class RenderWindow
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Texture* signTex;

public:
	RenderWindow();
	void loadImage(const char* filepath);
	SDL_Renderer* getRenderer();
	SDL_Texture* getTexture();
	void clearRenderer();
	void destroy();
	void render(SDL_Rect src, SDL_Rect dst);
	void display();
	void subscreen(string title);
	void renderSubscreen();
	void updScoreBoard(int score);
	void sign();
	void renderSign();
};