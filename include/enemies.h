#ifndef ENEMIES_H
#define ENEMIES_H
#include<iostream>
#include<vector>
#include<SDL.h>
#include"player.h"
#include"barHP.h"
#include"Animation.h"
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
    bool isAttack = false;
    Uint32 shoottime;
    Animation explosion;
    Animation Enemies;
    bool animationInitialized = false;
};
void spawnenemy(vector<enemy>& e,player&p);
void updateEnemies(vector<enemy>& e,player&p);
void renderEnemies(vector<enemy>& e, SDL_Renderer* renderer,SDL_Texture*enemiesTexture);
void checkcollisionEandP(vector<enemy>& e,player&p,vector<hp>&HP,SDL_Renderer*renderer);
void checkcollisionEnemies(vector<enemy>& e,SDL_Renderer*renderer);

#endif
