#include "Player.h"
#include <SDL.h>

void createplayer(player& p) {
    p.x = 400;
    p.y = 500;
    p.rect.w = 50;
    p.rect.h = 50;
    p.speed = 700;
    p.score = 0;
    p.health = 1000;
    p.engine.setFrameDelay(3);  
    p.engine.setLoop(true);     
}

  void updateplayer(player & p) {
        p.rect.x = (int)p.x;
        p.rect.y = (int)p.y;

        
        if (p.x < 0) p.x = 0;
        if (p.x + p.rect.w > 800) p.x = 800 - p.rect.w;
        if (p.y < 0) p.y = 0;
        if (p.y + p.rect.h > 600) p.y = 600 - p.rect.h;
    }


void controlplayer(player& p, SDL_Event& e, const Uint8* keystates, float Time) {
    float velocityX = 0.0;
    float velocityY = 0.0;

    if (keystates[SDL_SCANCODE_RIGHT]) velocityX += p.speed;
    if (keystates[SDL_SCANCODE_LEFT])  velocityX -= p.speed;
    if (keystates[SDL_SCANCODE_UP])    velocityY -= p.speed;
    if (keystates[SDL_SCANCODE_DOWN])  velocityY += p.speed;

        p.x += velocityX * Time;
        p.y += velocityY * Time;

}

void renderplayer(player& p, SDL_Renderer* renderer) {
   
    SDL_Rect engineRect;
    engineRect.w = 64;
    engineRect.h = 64;
    engineRect.x = p.rect.x;
    engineRect.y = p.rect.y;

    SDL_Texture* currentFrame = p.engine.getCurrentFrame();
    if (currentFrame) {
        SDL_RenderCopy(renderer, currentFrame, nullptr, &engineRect);
    }
}
