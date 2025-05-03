#include "animation.h"
#include <SDL.h>

void Animation::addFrame(SDL_Texture* texture) {
    frames.push_back(texture);
}

void Animation::setFrameDelay(int delay)
{
    frameDelay = delay;
}
void Animation::setLoop(bool Loop)
{
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

// Hàm vẽ animation tại vị trí (x, y)
void Animation::render(SDL_Renderer* renderer, int x, int y) {
    if (!frames.empty()) {
        // Tạo rect để vẽ texture tại vị trí (x, y)
        SDL_Rect destRect = { x, y, 50, 50 };  // Kích thước có thể điều chỉnh
        SDL_RenderCopy(renderer, frames[currentFrame], nullptr, &destRect);
    }
}

// Hàm kiểm tra nếu animation đã hoàn thành (đã đến frame cuối)
bool Animation::isFinished() const {
    return currentFrame == frames.size() - 1;
}

SDL_Texture* Animation::getCurrentFrame() const
{
    if (!frames.empty()) {
        return frames[currentFrame];
    }
    return nullptr;
}
// Hàm thêm frame vào engine animation
void EffectManager::addEngineFrame(SDL_Texture* texture) {
    engineAnimation.addFrame(texture);
}

// Hàm thêm frame vào explosion animation
void EffectManager::addExplosionFrame(SDL_Texture* texture) {
    explosionAnimation.addFrame(texture);
}

// Hàm thêm frame vào bomb explosion animation
void EffectManager::addBombExplosionFrame(SDL_Texture* texture) {
    bombExplosionAnimation.addFrame(texture);
}

// Hàm cập nhật tất cả các animation trong EffectManager
void EffectManager::update() {
    engineAnimation.update();
    explosionAnimation.update();
    bombExplosionAnimation.update();
}

// Hàm render tất cả các animation trong EffectManager
void EffectManager::render(SDL_Renderer* renderer, int x, int y) {
    engineAnimation.render(renderer, x, y);  // Vẽ animation động cơ máy bay
    explosionAnimation.render(renderer, x, y);  // Vẽ animation hiệu ứng nổ
    bombExplosionAnimation.render(renderer, x, y);  // Vẽ animation hiệu ứng bom nổ
}
