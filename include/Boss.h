#ifndef BOSS_H
#define BOSS_H
//quan li boss
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
    bool isExplode = false;
    int explosionRadius;
    int explosionY;
    int explosionTimer = 0;
    bool explosion = false;
    bool remove = false;
    Uint32 bombstart= 0;

    Animation explosionbomb;
};
struct Boss {
    SDL_Rect rect;
    int health = 5000;
    int speedX;
    int shootCooldown;
    int bombCooldown;
    int distance=-50;
    std::vector<Bullet> bullets;
    std::vector<Bomb> bombs;
  //  Animation explosionbomb;
};

Boss createBoss(int x, int y);


void initBoss(Boss& boss);
void updateBoss(Boss& boss, player& p, vector<hp>& HP);
void updatebomb(Boss& boss, player& p);
void renderBoss(Boss& boss, SDL_Renderer* renderer,SDL_Texture*bombTexture,SDL_Texture*bossTexture,SDL_Texture*bulletsBossTexture);

#endif

