#include<SDL.h>
#include<SDL_ttf.h>

#include"Button.h"

using namespace std;
const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600, BUTTON_WIDTH = 100, BUTTON_HEIGHT = 80;
const SDL_Color red = { 255, 0, 0, 0 }, blue = { 0, 0, 255, 0 };

Button::Button(int _x, int _y, RenderWindow& screen, string name)
{
	texture = NULL;
	x = _x;
	y = _y;
	TTF_Font* font = TTF_OpenFont("VTC-GarageSale.ttf", 80);
	SDL_Surface* sur = TTF_RenderText_Solid(font, name.c_str(), red);
	defaultTex = SDL_CreateTextureFromSurface(screen.getRenderer(), sur);
	sur = TTF_RenderText_Solid(font, name.c_str(), blue);
	clickedTex = SDL_CreateTextureFromSurface(screen.getRenderer(), sur);
	SDL_FreeSurface(sur);
}

bool Button::check(int _x, int _y, RenderWindow& screen)
{
	if (_x >= x && _x < x + BUTTON_WIDTH && _y >= y && _y < y + BUTTON_HEIGHT)
	{
		texture = clickedTex;
		return 1;
	}
	texture = defaultTex;
	return 0;
}

void Button::renderButton(RenderWindow& screen)
{
	SDL_Rect dst = { x, y, BUTTON_WIDTH, BUTTON_HEIGHT };
	SDL_RenderCopy(screen.getRenderer(), texture, NULL, &dst);
	return;
}