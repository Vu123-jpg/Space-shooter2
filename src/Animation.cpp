#include "Animation.h"
#include <SDL.h>

Animation::Animation() : currentFrame(0), frameDelay(100), frameTime(0), loop(true) {}

void Animation::addFrame(SDL_Texture* texture) {
    frames.push_back(texture);
}

void Animation::setFrameDelay(int delay) {
    frameDelay = delay;
}


void Animation::setLoop(bool Loop) {
    loop = Loop;
}

void Animation::update() {
    frameTime++;
  
    if (frameTime >= frameDelay) {
        frameTime = 0;  
        currentFrame++;

      
        if (currentFrame >= frames.size()) {
            if (loop) {
                currentFrame = 0;  
            }
            else {
                currentFrame = frames.size() - 1;  
            }
        }
    }
}

//vi tri
void Animation::render(SDL_Renderer* renderer, int x, int y) {
    if (!frames.empty()) {
        SDL_Rect destRect = { x, y, 64, 64 };  
        SDL_RenderCopy(renderer, frames[currentFrame], nullptr, &destRect);  
    }
}

bool Animation::isFinished() const {
    return currentFrame == frames.size() - 1;  
}

SDL_Texture* Animation::getCurrentFrame() const {
    if (!frames.empty()) {
        return frames[currentFrame];
    }
    return nullptr;
}

/*
void EffectManager::addEngineFrame(SDL_Texture* texture) {
    engineAnimation.addFrame(texture);  
}

void EffectManager::addExplosionFrame(SDL_Texture* texture) {
    explosionAnimation.addFrame(texture); 
}


void EffectManager::addBombExplosionFrame(SDL_Texture* texture) {
    bombExplosionAnimation.addFrame(texture);
}


void EffectManager::update() {
    engineAnimation.update(); 
    explosionAnimation.update();  // Cập nhật animation nổ
    bombExplosionAnimation.update();  
}

// Render tất cả các animation trong EffectManager tại (x, y)
void EffectManager::render(SDL_Renderer* renderer, int x, int y) {
    engineAnimation.render(renderer, x, y);  // Render animation động cơ
    explosionAnimation.render(renderer, x, y);  // Render animation nổ
    bombExplosionAnimation.render(renderer, x, y);  // Render animation bom nổ
}
*/