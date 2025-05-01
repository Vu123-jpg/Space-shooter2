#ifndef ENEMIES_H
#define ENEMIES_H
#include<iostream>
#include<vector>
#include<SDL.h>
#include"player.h"
#include"barHP.h"
#include<SDL_image.h>
struct bullet;
using namespace std;
struct enemy {
    SDL_Rect rect;
    float poseY;
    float posdisY;
    float poseX;
    float zigzagOffset = 0;
    int movetype;
    int distance;
    int speed;
    int health;
    Uint32 shoottime;
};
void spawnenemy(vector<enemy>& e,player&p);
void updateEnemies(vector<enemy>& e,player&p);
void renderEnemies(vector<enemy>& e, SDL_Renderer* renderer, SDL_Texture* enemyTexture);
void checkcollisionEandP(vector<enemy>& e,player&p,vector<hp>&HP);
void checkcollisionEnemies(vector<enemy>& e);

#endif
