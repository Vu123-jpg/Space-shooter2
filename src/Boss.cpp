#include "boss.h"

void initBoss(Boss& boss) {
    boss.rect = { 300, 50, 64, 64 }; 
    boss.speedX = 2;

    boss.shootCooldown = 0;
    boss.bombCooldown = 60; 

    boss.bullets.clear();
    boss.bombs.clear();
}

void updateBoss(Boss& boss){
    // Di chuyển ngang
    boss.rect.x += boss.speedX;
    if (boss.rect.x <= 200 || boss.rect.x + boss.rect.w >= 600)
    {
        boss.speedX = -boss.speedX;
   }

    // Bắn đạn
    if (boss.shootCooldown <= 0) {
        Bullet b = {
            { boss.rect.x + boss.rect.w / 2 - 5, boss.rect.y + boss.rect.h, 10, 20 },
            5
        };
        boss.bullets.push_back(b);
        boss.shootCooldown = 30; // delay giữa các lần bắn
    }
    else {
        boss.shootCooldown--;
    }

    // Ném bom
    if (boss.bombCooldown <= 0) {
        Bomb bomb = {
            { boss.rect.x + boss.rect.w / 2 - 8, boss.rect.y + boss.rect.h, 16, 16 },
            3
        };
        boss.bombs.push_back(bomb);
        boss.bombCooldown = 120;
    }
    else {
        boss.bombCooldown--;
    }

    // Cập nhật đạn
    for (int i = 0; i < boss.bullets.size(); ++i) {
        boss.bullets[i].rect.y += boss.bullets[i].speed;
    }

    // Xóa đạn vượt khỏi màn hình
    for (int i = boss.bullets.size() - 1; i >= 0; --i) {
        if (boss.bullets[i].rect.y > 600) {
            boss.bullets.erase(boss.bullets.begin() + i);
        }
    }

    // Cập nhật bom
    for (int i = 0; i < boss.bombs.size(); ++i) {
        boss.bombs[i].rect.y += boss.bombs[i].speed;
    }

    // Xóa bom vượt khỏi màn hình
    for (int i = boss.bombs.size() - 1; i >= 0; --i) {
        if (boss.bombs[i].rect.y > 600) {
            boss.bombs.erase(boss.bombs.begin() + i);
        }
    }
}

void renderBoss(Boss&boss,SDL_Renderer*renderer){
    // Vẽ boss
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Đỏ
    SDL_RenderFillRect(renderer, &boss.rect);

    // Vẽ đạn
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Vàng
    for (auto& b : boss.bullets) {
        SDL_RenderFillRect(renderer, &b.rect);
    }

    // Vẽ bom
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Xanh dương
    for (auto& bomb : boss.bombs) {
        SDL_RenderFillRect(renderer, &bomb.rect);
    }
}
