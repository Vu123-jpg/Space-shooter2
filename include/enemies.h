#ifndef ENEMIES_H
#define ENEMIES_H
#include<iostream>
#include<vector>
#include<SDL.h>
#include<SDL_image.h>
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
void renderEnemies(vector<enemy>& e, SDL_Renderer* renderer, SDL_Texture* enemyTexture);
void checkcollisionenemy(vector<enemy>& e);

#endif
