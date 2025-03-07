#include<iostream>
#include<SDL.h>
#include"player.h"
#include"bullets.h"
#include<vector>
using namespace std;
vector<bullet> b1;
void createplayer(player& p)
{
	p.rect.x = 400;
	p.rect.y = 500;
	p.rect.w = 50;
	p.rect.h = 50;
	p.speed = 40;
	p.score = 0;
	p.health = 1000;
}
void updateplayer(player& p)
{
	if (p.rect.x < 0) p.rect.x = 0;
	if (p.rect.x + p.rect.w > 800) p.rect.x = 800 - p.rect.w;
}
/*void controlplayer(player& p, SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT:
			p.rect.x += p.speed;
			break;
		case SDLK_LEFT:
			p.rect.x -= p.speed;
			break;
		}

	}
}*/
void renderplayer(player& p, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &p.rect);
}
