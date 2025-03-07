#ifndef PLAYER_H
#define PLAYER_H
#include<SDL.h>
#include<iostream>

struct player
{
	SDL_Rect rect;
	int speed;
	int score;
	int health;
};
void createplayer(player& p);
void updateplayer(player& p);
/*void controlplayer(player& p, SDL_Event& e);*/
void renderplayer(player& p, SDL_Renderer* renderer);
#endif 

