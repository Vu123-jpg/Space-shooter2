#ifndef BARHP_H
#define BARHP_H\
//quan li thanh mau va thnah no cua nguoi choi
#include<SDL.h>
#include"player.h"
#include<vector>
using namespace std;
struct hp
{
	SDL_Rect rect;
};
struct combo
{
	SDL_Rect rect;
};
void createbarhp(vector<hp>& HP); //thanh mau nguoi choi
void updatebarhp(vector<hp>& HP, player& p);
void renderbarhp(SDL_Renderer* renderer, vector<hp>& HP);

void createHPboss( vector<hp>&HPboss);//thanh mau cua boss
void updateHPboss(vector<hp>& HPboss);
void renderHPboss(SDL_Renderer*renderer,vector<hp>&HPboss);

void createbarcombo(vector<combo>&cb,player&p);
void renderbarcombo(SDL_Renderer* renderer, vector<combo>& cb);
void renderbarcombofull(SDL_Renderer* renderer, vector<combo>& cb);//chuyen mau khi day no
#endif