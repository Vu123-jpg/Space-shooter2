#include<iostream>
#include<vector>
#include<SDL.h>
#include"bullets.h"
#include"player.h"
#include"enemies.h"
#include<ctime>
void createplayerbullet(vector<bullet>& b1, player& p)
{
	bullet temp;
	temp.rect.x = p.rect.x + p.rect.w / 2;
	temp.rect.y = p.rect.y;
	temp.rect.w = 10;
	temp.rect.h = 10;
	temp.speed = 1;
	b1.push_back(temp);
}
void createenemiesbullet(vector<bullet>& b2, vector<enemy>& e)
{
	int n = e.size();
	Uint32 curenttime = SDL_GetTicks();
	for (int i = 0;i < n;i++)
	{
		if (curenttime >= e[i].shoottime)
		{
			bullet tmp;
			tmp.rect.x = e[i].rect.x + e[i].rect.w / 2;
			tmp.rect.y = e[i].rect.y;
			tmp.posY = tmp.rect.y;
			tmp.rect.w = 10;
			tmp.rect.h = 10;
			tmp.speed = 1.0;
			b2.push_back(tmp);
			e[i].shoottime = curenttime + (rand() % 2000 + 1000);
		}
 
	}
}
void updateplayerbullet(vector<bullet>& b1)
{
	for (int i =b1.size()-1;i >=0;i--)
	{
		b1[i].rect.x += b1[i].speed / 10;
		b1[i].rect.y -= b1[i].speed;
		if (b1[i].rect.y < 0)
		{
			b1.erase(b1.begin() + i);
		}
	}
}
void updateenemiesbullet(vector<bullet>& b2)
{
	for (int i = b2.size()-1;i >=0;i--)
	{
		b2[i].posY += b2[i].speed / 10;
		b2[i].rect.y = (int)b2[i].posY;
		if (b2[i].rect.y >600)
		{
			b2.erase(b2.begin() + i);
		}
	}
}
void renderplayerbullet(vector<bullet>& b1, SDL_Renderer* renderer)
{
	int m = b1.size();
	for (int i = 0;i < m;i++)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
		SDL_RenderFillRect(renderer, &b1[i].rect);
	}
}
void renderenemiesbullet(vector<bullet>& b2, SDL_Renderer* renderer)
{
	int k = b2.size();
	for (int i = 0;i < k;i++)
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(renderer, &b2[i].rect);
	}
}
void checkcollision1(vector<bullet>& b1, vector<enemy>&e,player&p)
{
	for (int i = b1.size()-1;i >=0;i--)
	{
		for (int j = e.size()-1;j>=0;j--)
		{
			if (SDL_HasIntersection(&b1[i].rect, &e[j].rect))
			{
				p.score += 10;
				cout << "diem" << " " << p.score;
				cout << endl;
				b1.erase(b1.begin() + i);
				e.erase(e.begin() + j);
				break;
			}

		}
	}
}
void checkcollision2(vector<bullet>& b2, player& p)
{
	for (int i =b2.size()-1;i>=0;i--)
	{
		if (SDL_HasIntersection(&b2[i].rect, &p.rect))
		{
			b2.erase(b2.begin() + i);
			p.health -= 100;
			cout << "mau hien tai" << p.health;
			cout << endl;
		}
	}
}
