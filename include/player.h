#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "Animation.h"

//quan li nguoi choi
struct player {
    SDL_Rect rect;
    float x, y;
    int speed;
    int score;
    int highscore = 0;
    int health;
    int combo = 0;
    Animation engine;  
};

void createplayer(player& p);          
void updateplayer(player& p);          
void controlplayer(player& p, SDL_Event& e, const Uint8* keystates, float Time); 
void renderplayer(player& p, SDL_Renderer* renderer); // Vẽ player lên màn hình

#endif // PLAYER_H
