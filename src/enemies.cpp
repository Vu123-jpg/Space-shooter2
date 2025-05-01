#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include"enemies.h"
#include"bullets.h"
#include"player.h"
#include"barHP.h"
#include<cstdlib>
#include<unordered_set>
using namespace std;
int maxEnemies = 10;
int cols = 10; // cot de luu ke dich 
int colwidth = 800 / cols;
void spawnenemy(vector<enemy>& e,player&p) {
	unordered_set<int>existcols;
	int startY = 50; 
	for (int i = 0;i < e.size();i++)
	{
		int cole = e[i].rect.x / colwidth;
			existcols.insert(cole);
	}
	while (e.size() < maxEnemies)
	{
		int randcols = rand() % cols;
		if (existcols.count(randcols)) continue;
		enemy tmp;
		tmp.rect.x = randcols * colwidth + colwidth / 4;
		tmp.rect.y = startY - (rand() % 152);
		tmp.poseY = tmp.rect.y;
		tmp.rect.w = 30;
		tmp.rect.h = 30;
		tmp.speed = 20;
		tmp.distance = 0;
		if (p.score < 1000)
		{
			tmp.health = 50;
		}
		else
		{
			tmp.health = 100;
		}
		tmp.posdisY = tmp.distance;
		tmp.shoottime = SDL_GetTicks() + (rand() % 2000 + 1000);
		e.push_back(tmp);
	}

}

void updateEnemies(vector<enemy>& e, player& p) {
	if (e.empty()) return;
	for (int i = 0; i < e.size(); i++) {
		if (e[i].posdisY < 150) {
			e[i].poseY += e[i].speed / 10;
			e[i].rect.y = (int)e[i].poseY;
			e[i].posdisY += e[i].speed / 10;
		}

		if (p.score >= 1000) {
				e[i].rect.y += e[i].speed / 5;
		}

		if (e[i].rect.y > 600) {
			e[i].rect.y = -50;
			e[i].rect.x = rand() % 800;
			e[i].posdisY = 150;
			e[i].speed = 20;
		}

		if (e[i].rect.y >= 150 && e[i].posdisY >= 150) {
			e[i].distance = 150;
		}
	}
}


void renderEnemies(vector<enemy>& e, SDL_Renderer* renderer, SDL_Texture* enemyTexture) {
	if (e.empty()) return;

	for (int i = 0;i<(int)e.size();i++) {
		SDL_RenderCopy(renderer, enemyTexture, nullptr, &e[i].rect);
	}
}

void checkcollisionEandP(vector<enemy>& e,player&p,vector<hp>&HP)
{
	for (int i = 0;i < e.size();i++)
	{
		if (SDL_HasIntersection(&e[i].rect, &p.rect))
		{
			p.health -= 100;
			updatebarhp(HP, p);
			if (!e.empty())
			{
				e.erase(e.begin() + i);
				i--;
			}
		}
	}
}

void checkcollisionEnemies(vector<enemy>& e)
{
	vector<bool> toRemove(e.size(), false);// danh dau nhung ke dich va cham

	for (int i = 0; i < e.size(); ++i)
	{
		for (int j = i + 1; j < e.size(); ++j)
		{
			if (!toRemove[i] && !toRemove[j] &&
				SDL_HasIntersection(&e[i].rect, &e[j].rect))
			{
				toRemove[i] = true;
				toRemove[j] = true;
			}
		}
	}

	// Xóa ke dich va cham voi nhau
	for (int i = e.size() - 1; i >= 0; --i)
	{
		if (toRemove[i])
		{
			e.erase(e.begin() + i);
		}
	}
}
