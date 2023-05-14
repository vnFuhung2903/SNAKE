#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<string>

#include"RenderWindow.h"

using namespace std;
const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;

RenderWindow::RenderWindow()
{
	if (SDL_INIT_EVERYTHING == 0 || TTF_Init() == -1)
		SDL_Log("Failed to init");

	window = SDL_CreateWindow("SNAKE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT + 16, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void RenderWindow::loadImage(const char* filepath)
{
	SDL_Surface* loadedImage = IMG_Load(filepath);
	SDL_SetColorKey(loadedImage, SDL_TRUE, SDL_MapRGB(loadedImage->format ,0, 0xff, 0xff));
	texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
}

SDL_Renderer* RenderWindow::getRenderer()
{
	return renderer;
}

SDL_Texture* RenderWindow::getTexture()
{
	return texture;
}

void RenderWindow::render(SDL_Rect src, SDL_Rect dst)
{
	SDL_RenderCopy(renderer, texture, &src, &dst);
}

void RenderWindow::clearRenderer()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::destroy()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
}

void RenderWindow::subscreen(string title)
{
	TTF_Font* font = TTF_OpenFont("VintageOne.ttf", 80);
	SDL_Color color = { 255, 0, 0, 0 };
	SDL_Surface* sur = TTF_RenderText_Solid(font, title.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, sur);
	SDL_FreeSurface(sur);
}

void RenderWindow::renderSubscreen()
{
	SDL_Rect dst = { 0, 100, SCREEN_WIDTH, 80 };
	SDL_RenderCopy(renderer, texture, NULL, &dst);
	display();
}
void RenderWindow::scoreBoard(int score)
{
	TTF_Font* font = TTF_OpenFont("VTC-GarageSale.ttf", 30);
	SDL_Color color = { 255, 0, 0, 0 };
	string scoreInfo = "SCORE: " + to_string(score);
	SDL_Surface* sur = TTF_RenderText_Solid(font, scoreInfo.c_str(), color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, sur);
	SDL_FreeSurface(sur);
	SDL_Rect dst = { 700, SCREEN_HEIGHT, 100, 16 };
	SDL_RenderCopy(renderer, tex, NULL, &dst);
}

void RenderWindow::sign()
{
	TTF_Font* font = TTF_OpenFont("VTC-GarageSale.ttf", 30);
	SDL_Color color = { 0, 0, 255, 0 };
	SDL_Surface* sur = TTF_RenderText_Solid(font, "--NGUYEN PHU HUNG--", color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, sur);
	SDL_FreeSurface(sur);
	SDL_Rect dst = { 300, SCREEN_HEIGHT, 200, 16 };
	SDL_RenderCopy(renderer, tex, NULL, &dst);
}