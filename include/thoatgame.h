#ifndef THOATGAME_H
#define THOATGAME_H
#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>
#include"bullets.h"
#include"player.h"
#include"barHP.h";
void thoatgame(SDL_Renderer* renderer, bool& restart);
void resetgame(vector<bullet>& b1, vector<bullet>& b2, vector<enemy>& e, player& p, vector<hp>& HP, vector<bullet>& b3);
void renderscore(SDL_Renderer* renderer,TTF_Font*font,  player& p);
void rendergameover(SDL_Renderer* renderer, TTF_Font* font);
void renderBackground(SDL_Renderer* renderer, SDL_Texture* backgroundTexture);
#endif
