#ifndef BARHP_H
#define BARHP_H
#include<SDL.h>
#include"player.h"
#include<vector>
using namespace std;
struct hp
{
	SDL_Rect rect;
};
void createbarhp(vector<hp>& HP);
void updatebarhp(vector<hp>& HP, player& p);
void renderbarhp(SDL_Renderer* renderer, vector<hp>& HP);
#endif