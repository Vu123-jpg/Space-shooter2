#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <vector>

// quan li animation
struct Animation {
    std::vector<SDL_Texture*> frames;  
    int currentFrame;
    int lastFrameTime;
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

#endif 
