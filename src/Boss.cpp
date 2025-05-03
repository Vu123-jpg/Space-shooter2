#include "boss.h"
#include "player.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include<SDL.h>
#include<SDL_image.h>
using namespace std;

bool checkExplosionCollision(SDL_Rect& bombRect, SDL_Rect& playerRect, int explosionRadius) {
    int bombX = bombRect.x + bombRect.w / 2;
    int bombY = bombRect.y + bombRect.h / 2;
    int playerX = playerRect.x + playerRect.w / 2;
    int playerY = playerRect.y + playerRect.h / 2;

    int deltaX = bombX - playerX;
    int deltaY = bombY - playerY;
    int distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    return distance <= explosionRadius;
}

void initBoss(Boss& boss) {
    boss.rect = { 300, 50, 64, 64 };  
    boss.speedX = 2;  
    boss.shootCooldown = 0;  
    boss.bombCooldown = 60;  

    boss.bullets.clear();  
    boss.bombs.clear(); 
}

void updateBoss(Boss& boss, player& p, vector<hp>& HP) {
    
    boss.rect.x += boss.speedX;
    if (boss.rect.x <= 200 || boss.rect.x + boss.rect.w >= 600) {
        boss.speedX = -boss.speedX;  
    }

    
    if (boss.shootCooldown <= 0) {
        Bullet b = {
            { boss.rect.x + boss.rect.w / 2 - 5, boss.rect.y + boss.rect.h, 10, 10 },
            5
        };
        boss.bullets.push_back(b);
        boss.shootCooldown = 30;
    }
    else {
        boss.shootCooldown--;
    }

  
    for (int i = boss.bullets.size() - 1; i >= 0; --i) {
        boss.bullets[i].rect.y += boss.bullets[i].speed;
        if (SDL_HasIntersection(&boss.bullets[i].rect, &p.rect)) {
            p.health -= 100;  
            updatebarhp(HP, p);  
            boss.bullets.erase(boss.bullets.begin() + i);  
            continue;
        }
        if (boss.bullets[i].rect.y > 600) {
            boss.bullets.erase(boss.bullets.begin() + i);  
        }
    }

    // Thả bom
    if (boss.bombCooldown <= 0) {
        Bomb bomb;
        bomb.rect = { boss.rect.x + boss.rect.w / 2 - 8, boss.rect.y + boss.rect.h, 25, 25 };
        bomb.speed = 3;
        bomb.isExploded = false;
        bomb.explosionRadius = 50;  
        bomb.explosionY = rand() % 200 + 300;  
        boss.bombs.push_back(bomb);
        boss.bombCooldown = 120;
    }
    else {
        boss.bombCooldown--;
    }

    
    updatebomb(boss, p);
}

void updatebomb(Boss& boss, player& p) {
    for (int i = boss.bombs.size() - 1; i >= 0; --i) {
        Bomb& bomb = boss.bombs[i];

        if (!bomb.isExploded) {
            bomb.rect.y += bomb.speed;

            if (bomb.rect.y >= bomb.explosionY) {
                bomb.isExploded = true;
                bomb.explosionTimer = 30;  
            }
        }
        else {
            if (bomb.explosionTimer > 0) {
                if (checkExplosionCollision(bomb.rect, p.rect, bomb.explosionRadius)) {
                    p.health -= 100;  
         
                }
                bomb.explosionTimer--;
            }
            else {
                boss.bombs.erase(boss.bombs.begin() + i);  
            }
        }
    }
}

void renderBoss(Boss& boss, SDL_Renderer* renderer) {
     
    SDL_Texture* explosion1 = IMG_LoadTexture(renderer, "asset/explosion1.png");
    SDL_Texture* explosion2 = IMG_LoadTexture(renderer, "asset/explosion2.png");
    SDL_Texture* explosion3 = IMG_LoadTexture(renderer, "asset/explosion3.png");
    SDL_Rect explosionRect;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &boss.rect);

    
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    for (auto& b : boss.bullets) {
        SDL_RenderFillRect(renderer, &b.rect);
    }

   
    for (auto& bomb : boss.bombs) {
        
        if (bomb.isExploded && bomb.explosionTimer > 0) {
            SDL_Rect explosionRect = {
                bomb.rect.x + bomb.rect.w / 2 - bomb.explosionRadius,
                bomb.rect.y + bomb.rect.h / 2 - bomb.explosionRadius,
                128,128
            };
            SDL_Texture* currentFrame = boss.explosionbomb.getCurrentFrame();
            if (currentFrame) {
                SDL_RenderCopy(renderer, currentFrame, nullptr, &explosionRect);
            }
        }
    }
    SDL_DestroyTexture(explosion1);
    SDL_DestroyTexture(explosion2);
    SDL_DestroyTexture(explosion3);
}
