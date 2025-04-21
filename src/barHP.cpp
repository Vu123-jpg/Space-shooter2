#include <iostream>
#include <vector>
#include <SDL.h>
#include "barHP.h"
#include"bullets.h"
#include"player.h"
using namespace std;

void createbarhp(vector<hp>& HP)
{
    HP.clear();
    int startX = 650;
    for (int i = 0; i < 10; i++) {
        hp newHP;
        newHP.rect.x = startX + i * 10;
        newHP.rect.y = 10;
        newHP.rect.w = 10;
        newHP.rect.h = 20;
        HP.push_back(newHP);
    }
}

void updatebarhp(vector<hp>& HP, player& p)
{
        HP.pop_back(); 
     
}

void renderbarhp(SDL_Renderer* renderer, vector<hp>& HP)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (size_t i = 0; i < HP.size(); i++)
    {
        SDL_RenderFillRect(renderer, &HP[i].rect);
    }
}
void createbarcombo(vector<combo>&cb, player& p)
{
    cb.clear();
    if (p.combo == 0) return;
    int startX = 650;
    combo newcb;
    for(int i=0;i<p.combo/5;i++)
    {
        newcb.rect.x = startX + i * 10;
        newcb.rect.y = 35;
        newcb.rect.w = 10;
        newcb.rect.h = 20;
        cb.push_back(newcb);
        if (cb.size() == 10) return;
    }
}
void renderbarcombo(SDL_Renderer* renderer, vector<combo>& cb)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for (size_t i = 0; i < cb.size(); i++)
    {
        SDL_RenderFillRect(renderer, &cb[i].rect);
    }
}
void renderbarcombofull(SDL_Renderer* renderer, vector<combo>& cb)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (size_t i = 0;i < cb.size();i++)
    {
        SDL_RenderFillRect(renderer, &cb[i].rect);
    }
}
