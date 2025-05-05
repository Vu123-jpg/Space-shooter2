#ifndef GAME_H
#define GAME_H
#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>
#include"bullets.h"
#include"player.h"
#include"barHP.h";
#include"Boss.h"
#include"Animation.h"
//quan li cac su kien cua game
void startgame(SDL_Renderer* renderer, bool &gamestart);
void renderstartgame(SDL_Renderer* renderer, SDL_Texture* startTexture); //man hinh vao game
void endgame(SDL_Renderer* renderer, bool& restart);
void renderendgame(SDL_Renderer* renderer, SDL_Texture* endTexture);//man hinh ket thuc game
void resetgame(vector<bullet>& b1, vector<bullet>& b2, vector<enemy>& e, player& p, vector<hp>& HP, vector<bullet>& b3,Boss&boss,bool&bossSpawned,vector<combo>&cb);
void renderscore(SDL_Renderer* renderer,TTF_Font*font,  player& p);
void renderBackground(SDL_Renderer* renderer, SDL_Texture* backgroundTexture);
void loadVictoryAnim(SDL_Renderer* renderer);
void renderWingame(SDL_Renderer* renderer);
#endif
