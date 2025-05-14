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
    Uint32 currentTime = SDL_GetTicks(); 
    if (currentTime - lastFrameTime >= frameDelay) {
        lastFrameTime = currentTime;  

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

