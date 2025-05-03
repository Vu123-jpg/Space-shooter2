#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <vector>

// quan li animation
struct Animation {
    std::vector<SDL_Texture*> frames;  
    int currentFrame;                  
    int frameDelay;                    
    int frameTime;                    
    bool loop;                         

    Animation();  // khoi tao

    void addFrame(SDL_Texture* texture);  
    void setFrameDelay(int delay);        
    void setLoop(bool Loop);              
    void update();                        
    void render(SDL_Renderer* renderer, int x, int y);  
    bool isFinished() const;              
    SDL_Texture* getCurrentFrame() const; 
}; 
/*
// Cấu trúc EffectManager để quản lý các hiệu ứng (động cơ, nổ, bom nổ)
struct EffectManager {
    Animation engineAnimation;           // Animation cho động cơ máy bay
    Animation explosionAnimation;        // Animation cho hiệu ứng nổ
    Animation bombExplosionAnimation;    // Animation cho hiệu ứng bom nổ

    // Hàm thêm các frame vào các animation
    void addEngineFrame(SDL_Texture* texture);
    void addExplosionFrame(SDL_Texture* texture);
    void addBombExplosionFrame(SDL_Texture* texture);

    // Hàm cập nhật tất cả các animation trong EffectManager
    void update();

    // Hàm render tất cả các animation trong EffectManager
    void render(SDL_Renderer* renderer, int x, int y);
};
*/
#endif 
