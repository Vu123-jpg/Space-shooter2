#include<iostream>
#include<vector>
#include<SDL.h>
#include<cmath>
#include"game.h"
#include"bullets.h"
#include"player.h"
#include"enemies.h"
#include"barHP.h"
#include<ctime>
bool restart;
void createplayerbullet(vector<bullet>& b1, player& p)
{
	bullet temp;
	temp.rect.x = p.rect.x + p.rect.w / 2;
	temp.rect.y = p.rect.y;
	temp.posY = temp.rect.y;
	temp.rect.w = 20;
	temp.rect.h = 20;
	temp.speed = 20.0;
	b1.push_back(temp);
}
void createenemiesbullet(vector<bullet>& b2, vector<enemy>& e, player& p)
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
			tmp.speed = 15.0;
			if (p.score >= 1000)
			{
				tmp.speed = 30.0;
			}
			b2.push_back(tmp);
			e[i].shoottime = curenttime + (rand() % 2000 + 1000);

		}
	}
}
void updateplayerbullet(vector<bullet>& b1)
{
	for (int i =b1.size()-1;i >=0;i--)
	{
		b1[i].posY -= b1[i].speed / 2;
		b1[i].rect.y = (int)b1[i].posY;
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
		b2[i].posY += b2[i].speed / 3;
		b2[i].rect.y = (int)b2[i].posY;
		if (b2[i].rect.y >600)
		{
			b2.erase(b2.begin() + i);
		}
	}
}
void renderplayerbullet(vector<bullet>& b1, SDL_Renderer* renderer,SDL_Texture*bulletsTexture)
{
	int m = b1.size();
	for (int i = 0;i < m;i++)
	{
		SDL_RenderCopy(renderer, bulletsTexture, nullptr, &b1[i].rect);
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
void createnuclearbomb(vector<bullet>& b3, player& p)
{
	bullet b;
	b.rect.x = p.rect.x + p.rect.w / 2;
	b.rect.y = p.rect.y;
	b.posY = b.rect.y;
	b.rect.w = 40;
	b.rect.h = 40;
	b.speed = 20;
	b3.push_back(b);
}
void updatenuclearbomb(vector<bullet>& b3)
{
	for (int i = b3.size() - 1;i >= 0;i--)
	{
		b3[i].posY -= b3[i].speed / 10;
		b3[i].rect.y = (int)b3[i].posY;
		if (b3[i].rect.y < 0)
		{
			b3.erase(b3.begin() + i);
		}
	}
}
void rendernuclearbomb(vector<bullet>&b3,SDL_Renderer*renderer)
{
	int n = b3.size();
	for (int i = 0;i <n;i++)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
		SDL_RenderFillRect(renderer, &b3[i].rect);
	}
}
void nuclearbombexplode(vector<bullet>& b3, vector<enemy>& e,player&p,vector<bullet>&b2,SDL_Renderer*renderer)
{
	for (int i = b3.size()-1;i >= 0;i--)
	{
		if (b3[i].rect.y <= 100)
		{
			b3.erase(b3.begin() + i);
			e.clear();
			b2.clear();
			p.score += 100;
			SDL_Rect fullScreenRect = { 0, 0, 800, 600 };

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128); 
			SDL_RenderFillRect(renderer, &fullScreenRect);

			
			SDL_Delay(100);
		}
	}
}
void checkcollision1(vector<bullet>& b1, vector<enemy>&e,player&p,vector<combo>&cb,SDL_Renderer*renderer)
{
	SDL_Texture* explosion1 = IMG_LoadTexture(renderer, "asset/explosion1.png");
	SDL_Texture* explosion2 = IMG_LoadTexture(renderer, "asset/explosion2.png");
	SDL_Texture* explosion3 = IMG_LoadTexture(renderer, "asset/explosion3.png");
	SDL_Rect explosionRect;
	explosionRect.w = 128;
	explosionRect.h = 128;

	for(int i=b1.size()-1;i>=0;i--)
	{
		for(int j=e.size()-1;j>=0;j--)
		{
			if (SDL_HasIntersection(&b1[i].rect, &e[j].rect))
			{
				   e[j].health -= 50;
				   if (e[j].health == 0)
				   {   
					   p.score += 10;
					   p.combo++;
					   explosionRect.x = e[j].rect.x;
					   explosionRect.y = e[j].rect.y;
					   e[j].explosion.addFrame(explosion1);
					   e[j].explosion.addFrame(explosion2);
					   e[j].explosion.addFrame(explosion3);
					   e[j].explosion.update();
					   e[j].explosion.setFrameDelay(500);
					   e[j].explosion.setLoop(false);
					   SDL_Texture* currentFrame = e[j].explosion.getCurrentFrame();
					   if (currentFrame) {
						   SDL_RenderCopy(renderer, currentFrame, nullptr, &explosionRect);
					   }
					   e.erase(e.begin() + j);
				   }
					createbarcombo(cb, p);
					b1.erase(b1.begin() + i);
					break;
			}

		}
	}
	SDL_DestroyTexture(explosion1);
	SDL_DestroyTexture(explosion2);
	SDL_DestroyTexture(explosion3);
}
void checkcollision2(vector<bullet>& b2, player& p,vector<hp>&HP,vector<combo>&cb)
{
	for (int i =b2.size()-1;i>=0;i--)
	{
		if (SDL_HasIntersection(&b2[i].rect, &p.rect))
		{
			b2.erase(b2.begin() + i);
			p.health -= 100;
			createbarcombo(cb, p);
			updatebarhp(HP, p);
		}
	}
}






