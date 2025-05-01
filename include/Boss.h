#ifndef BOSS_H
#define BOSS_H

#include <SDL.h>
#include <vector>

struct Bullet {
    SDL_Rect rect;
    int speed;
};

struct Bomb {
    SDL_Rect rect;
    int speed;
};

struct Boss {
    SDL_Rect rect;
    int health;
    int speedX;
    int shootCooldown;
    int bombCooldown;

    std::vector<Bullet> bullets;
    std::vector<Bomb> bombs;
};

// Hàm khởi tạo Boss
Boss createBoss(int x, int y);

// Các hàm xử lý boss
void initBoss(Boss& boss);
void updateBoss(Boss& boss);
void renderBoss(Boss& boss, SDL_Renderer* renderer);

#endif

