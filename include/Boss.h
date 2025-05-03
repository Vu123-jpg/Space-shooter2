#ifndef BOSS_H
#define BOSS_H

#include <SDL.h>
#include <vector>
#include"player.h"
#include"barHP.h"
#include"Animation.h"
struct Bullet {
    SDL_Rect rect;
    int speed;
};

struct Bomb {
    SDL_Rect rect;
    int speed;
    bool isExploded;
    int explosionRadius = 500;
    int explosionY;
    int explosionTimer;
};
struct Boss {
    SDL_Rect rect;
    int health = 5000;
    int speedX;
    int shootCooldown;
    int bombCooldown;

    std::vector<Bullet> bullets;
    std::vector<Bomb> bombs;
    Animation explosionbomb;
};

Boss createBoss(int x, int y);


void initBoss(Boss& boss);
void updateBoss(Boss& boss, player& p, vector<hp>& HP);
void updatebomb(Boss& boss, player& p);
void renderBoss(Boss& boss, SDL_Renderer* renderer);

#endif

