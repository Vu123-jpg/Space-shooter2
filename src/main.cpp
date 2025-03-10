#include<iostream>
#include<SDL.h>
#include<SDL_Rect.h>
#include"player.h"
#include"enemies.h"
#include"bullets.h"
#include"thoatgame.h"
using namespace std;
int main(int argc, char* agv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Space shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	bool running = true;
	bool gameover = false;
	SDL_Event event;
	player p;
	vector<enemy>e;
	vector<bullet>b1;
	vector<bullet>b2;
	createplayer(p);
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			if (event.type == SDL_KEYDOWN) {
				switch(event.key.keysym.sym ) {
				case SDLK_RIGHT:
					p.rect.x += p.speed;
					break;
				case SDLK_LEFT:
					p.rect.x -= p.speed;
					break;
				}
			}
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE)
			{
				createplayerbullet(b1, p);
			}

		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		updateplayer(p);
		renderplayer(p, renderer);
		spawnenemy(e);
		updateenemies(e);
		renderenemies(e, renderer);
		createenemiesbullet(b2, e);
		updateplayerbullet(b1);
		updateenemiesbullet(b2);
		renderplayerbullet(b1, renderer);
		renderenemiesbullet(b2, renderer);
		checkcollision1(b1,e,p);
		checkcollision2(b2, p);
		checkcollision3(e);
		if (p.health == 0)
		{
			bool restart = false;
			thoatgame(renderer, restart);
			if (restart)
			{
				p.health = 1000;
				p.score = 0;
			}
			else
			{
				running = false;

			}
		}

		SDL_RenderPresent(renderer);
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}