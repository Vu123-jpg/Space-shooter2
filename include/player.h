#ifndef PLAYER_H
#define PLAYER_H
#include<SDL.h>
#include<vector>
#include<iostream>

struct player
{
	SDL_Rect rect;
	int speed;
	int score;
	int health;
	int combo = 0;
};
void createplayer(player& p);
void updateplayer(player& p);
void controlplayer(player& p, SDL_Event& e);
void renderplayer(player& p, SDL_Renderer* renderer,SDL_Texture*planetexture);
#endif 

