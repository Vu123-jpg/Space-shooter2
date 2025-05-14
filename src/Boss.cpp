#include "boss.h"
#include "player.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
using namespace std;

bool checkExplosionCollision(SDL_Rect& bombRect, SDL_Rect& playerRect, int explosionRadius) {
    int bombX = bombRect.x + bombRect.w / 2;
    int bombY = bombRect.y + bombRect.h / 2;
    int playerX = playerRect.x + playerRect.w / 2;
    int playerY = playerRect.y + playerRect.h / 2;

    int deltaX = abs(bombX - playerX);
    int deltaY = abs(bombY-playerY);
    return (deltaX <= explosionRadius && deltaY <= explosionRadius);
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
    if (boss.distance < 130) {
        boss.distance += 2;
        if (boss.distance >= 130)
            boss.distance = 130;
        boss.rect.y = boss.distance;
    }
    if (boss.distance == 130)
    {
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
            boss.shootCooldown = 20;
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
    }
    
    if (boss.bombCooldown <= 0) {
        Bomb bomb;
        bomb.rect = { boss.rect.x + boss.rect.w / 2 - 8, boss.rect.y + boss.rect.h, 25, 25 };
        bomb.speed = 3;
        bomb.isExplode = false;
        bomb.explosionRadius = 100;  
        bomb.explosionY = rand() % 200 + 300;  
        boss.bombs.push_back(bomb);
        boss.bombCooldown = 80;
    }
    else {
        boss.bombCooldown--;
    }

    
    updatebomb(boss, p);
}

void updatebomb(Boss& boss, player& p) {
    for (int i = boss.bombs.size() - 1; i >= 0; --i) {
        Bomb& bomb = boss.bombs[i];

        if (!bomb.isExplode) {
            bomb.rect.y += bomb.speed;

            if (bomb.rect.y >= bomb.explosionY) {
                bomb.isExplode = true;
                bomb.explosionTimer = 30;  
            }
        }
        else {
            if (bomb.explosionTimer > 0) {
                if (checkExplosionCollision(bomb.rect, p.rect, bomb.explosionRadius)) {
                    p.health -= 100;  
                    cout << "trung bom" << endl;
                }
                bomb.explosionTimer--;
            }
            else {
                boss.bombs.erase(boss.bombs.begin() + i);  
            }
        }
    }
}

void renderBoss(Boss& boss, SDL_Renderer* renderer,SDL_Texture*bombTexture,SDL_Texture*bossTexture,SDL_Texture*bulletsBossTexture) {

    SDL_Texture* explosion1 = IMG_LoadTexture(renderer, "asset/explosion1.png");
    SDL_Texture* explosion2 = IMG_LoadTexture(renderer, "asset/explosion2.png");
    SDL_Texture* explosion3 = IMG_LoadTexture(renderer, "asset/explosion3.png");


   
    SDL_RenderCopy(renderer, bossTexture, nullptr, &boss.rect);


   
    for (auto& b : boss.bullets) {
        SDL_RenderCopy(renderer, bulletsBossTexture, nullptr, &b.rect);
    }

  
   
    for (auto& bomb : boss.bombs) {
        
        if (!bomb.isExplode) {
            SDL_RenderCopy(renderer, bombTexture, nullptr, &bomb.rect);
        }

      
        if (bomb.isExplode) {
            if (!bomb.explosion) {
                bomb.explosionbomb.addFrame(explosion1);
                bomb.explosionbomb.addFrame(explosion2);
                bomb.explosionbomb.addFrame(explosion3);
                bomb.explosionbomb.setFrameDelay(100);
                bomb.explosionbomb.setLoop(false);
                bomb.explosion= true;
                bomb.bombstart = SDL_GetTicks();
            }

          
            Uint32 now = SDL_GetTicks();
            Uint32 elapsed = now - bomb.bombstart;

           
            bomb.explosionbomb.update();

           
            if (elapsed <= 300) {
                SDL_Rect explosionRect = {
                    bomb.rect.x, bomb.rect.y,
                    128, 128
                };
                SDL_Texture* currentFrame = bomb.explosionbomb.getCurrentFrame();
                if (currentFrame) {
                    SDL_RenderCopy(renderer, currentFrame, nullptr, &explosionRect);
                }
            }
            else {
                bomb.remove = true; 
            }
        }
    }

    for (auto it = boss.bombs.begin(); it != boss.bombs.end(); ) {
        if (it->remove) {
            it = boss.bombs.erase(it);  
        }
        else {
            ++it;  
        }
    }
    SDL_DestroyTexture(explosion1);
    SDL_DestroyTexture(explosion2);
    SDL_DestroyTexture(explosion3);
}

