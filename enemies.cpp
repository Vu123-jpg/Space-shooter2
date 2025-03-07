#include<SDL.h>
#include<iostream>
#include"enemies.h"
#include<cstdlib>
using namespace std;
void spawnenemy(vector<enemy>& e) {
	int maxEnemies = 15;
	int cols = 50;
	int colwidth = 800 / cols;
	int startY = 50;
	while (e.size() < maxEnemies)
	{
		enemy tmp;
		tmp.rect.x = (rand() % cols) * colwidth + colwidth / 4;
		tmp.rect.y = startY - (rand() % 152);
		tmp.poseY = tmp.rect.y;
		tmp.rect.w = 30;
		tmp.rect.h = 30;
		tmp.speed = 1;
		tmp.distance = 0;
		tmp.posdisY = tmp.distance;
		tmp.shoottime = SDL_GetTicks() + (rand() % 2000 + 1000);
		e.push_back(tmp);
	}

}
void updateenemies(vector<enemy>& e)
{
	if (e.empty()) return;
	int n = e.size();
	for (int i=e.size()-1;i>=0;i--)
	{
		if (e[i].distance <150){
			e[i].poseY += e[i].speed / 10;
			e[i].rect.y = (int)e[i].poseY;
			e[i].posdisY += e[i].speed / 10;
			e[i].distance = (int)e[i].posdisY;
		}
		if (e[i].rect.y > 600)
		{
			e[i].rect.y = -50;
			e[i].rect.x = rand() % 800;
			e[i].distance = 0;
		}
	}
}
void renderenemies(vector<enemy>& e, SDL_Renderer* renderer)
{
	if (e.empty()) return;
	int n = e.size();
	for (int i = 0; i < n;i++)
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
		SDL_RenderFillRect(renderer, &e[i].rect);
	}
}
void checkcollision3(vector<enemy>&e)
{
	for (int i = e.size() - 1;i > 0;i--)
	{
		for (int j = i-1 ;j >= 0;j--)
		{
			if (SDL_HasIntersection(&e[i].rect,&e[j].rect))
			{
				e.erase(e.begin()+i);
				return;
			}
		}
	}
}