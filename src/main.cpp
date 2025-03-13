#include<iostream>
#include<SDL.h>
#include<SDL_Rect.h>
#include"player.h"
#include"enemies.h"
#include"bullets.h"
#include"thoatgame.h"
#include"barHP.h";
#include<SDL_image.h>
#include<SDL_ttf.h>
using namespace std;
int main(int argc, char* agv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	TTF_Font* font = TTF_OpenFont("asset/arial.ttf", 24);
	SDL_Window* window = SDL_CreateWindow("Space shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Color textColor = { 255, 255, 255, 255 };
	bool running = true;
	bool gameover = false;
	SDL_Event event;
	player p;
	vector<enemy>e;
	vector<bullet>b1;
	vector<bullet>b2;
	vector<bullet>b3;
	vector<hp>HP;
	createbarhp(HP);
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
				switch (event.key.keysym.sym) {
				case SDLK_RIGHT:
					p.rect.x += p.speed;
					break;
				case SDLK_LEFT:
					p.rect.x -= p.speed;
					break;
				case SDLK_SPACE:
					createplayerbullet(b1, p);
					break;
				}
				
			}
			if (p.combo >= 20)
			{
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
				{
					createnuclearbomb(b3, p);
					p.combo = 0;
				}
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
		updatenuclearbomb(b3);
		renderplayerbullet(b1, renderer);
		renderenemiesbullet(b2, renderer);
		rendernuclearbomb(b3, renderer);
		checkcollision1(b1,e,p);
		checkcollision2(b2, p, HP);
		booooom(b3, e, p);
		checkcollisionenemy(e);
		renderbarhp(renderer, HP);
		if (p.health == 0)
		{
			bool restart = false;
			rendergameover(renderer, font);
			SDL_RenderPresent(renderer);
			thoatgame(renderer, restart);
			if (restart)
			{
				resetgame(b1, b2, e, p, HP);

			}
			else
			{
				running = false;
				gameover = true;
			}
		}
		renderscore(renderer, font, p);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	TTF_CloseFont(font);
	TTF_Quit();

	return 0;
}