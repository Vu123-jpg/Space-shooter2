#ifndef ENEMIES_H
#define ENEMIES_H
#include<iostream>
#include<vector>
#include<SDL.h>
using namespace std;
struct enemy
{
	SDL_Rect rect;
	float speed;
	int distance;
	float poseY;
	float posdisY;
	Uint32 shoottime;
};
void spawnenemy(vector<enemy>& e);
void updateenemies(vector<enemy>& e);
void renderenemies(vector<enemy>& e, SDL_Renderer* renderer);
void checkcollision3(vector<enemy>&e);
#endif
