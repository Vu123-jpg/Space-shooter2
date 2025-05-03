#ifndef BULLETS_H
#define BULLETS_H
#include<iostream>
#include<vector>
#include<SDL.h>
#include"player.h"
#include"enemies.h"
#include"Animation.h"
#include"barHP.h"
using namespace std;
struct bullet
{
	SDL_Rect rect;
	float speed;
	float posY;
	Animation explosion;
};
void createplayerbullet(vector<bullet>& b1, player& p);
void createenemiesbullet(vector<bullet>& b2, vector<enemy>& e,player&p);
void updateplayerbullet(vector<bullet>& b1);
void updateenemiesbullet(vector<bullet>& b2);
void renderplayerbullet(vector<bullet>& b1, SDL_Renderer* renderer, SDL_Texture* bulletsTexture);
void renderenemiesbullet(vector<bullet>&b2, SDL_Renderer* renderer);
void createnuclearbomb(vector<bullet>& b3, player& p);
void updatenuclearbomb(vector<bullet>& b3);
void rendernuclearbomb(vector<bullet>& b3, SDL_Renderer* renderer);
void nuclearbombexplode(vector<bullet>& b3, vector<enemy>& e, player& p,vector<bullet>&b2,SDL_Renderer*renderer);
void checkcollision1(vector<bullet>& b1, vector<enemy>& e, player& p, vector<combo>& cb,SDL_Renderer*renderer);//va cham dan nguoi choi va ke dich
void checkcollision2(vector<bullet>& b2, player& p, vector<hp>& HP, vector<combo>& cb);//va cham dan ke dich va nguoi choi
#endif

