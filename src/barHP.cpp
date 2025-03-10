#include <iostream>
#include <vector>
#include <SDL.h>
#include "barHP.h"
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
