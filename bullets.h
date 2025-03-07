#ifndef BULLETS_H
#define BULLETS_H
#include<iostream>
#include<vector>
#include<SDL.h>
#include"player.h"
#include"enemies.h"
using namespace std;
struct bullet
{
	SDL_Rect rect;
	float speed;
	float posY;
};
void createplayerbullet(vector<bullet>& b1, player& p);
void createenemiesbullet(vector<bullet>& b2, vector<enemy>& e);
void updateplayerbullet(vector<bullet>& b1);
void updateenemiesbullet(vector<bullet>& b2);
void renderplayerbullet(vector<bullet>&b1, SDL_Renderer* renderer);
void renderenemiesbullet(vector<bullet>&b2, SDL_Renderer* renderer);
void checkcollision1(vector<bullet>& b1, vector<enemy>& e,player&p);
void checkcollision2(vector<bullet>& b2, player& p);
#endif

