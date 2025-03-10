#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>
#include<string>
#include"thoatgame.h"
#include"bullets.h"
#include"barHP.h"
using namespace std;
void thoatgame(SDL_Renderer* renderer, bool& restart) {
	bool gameover = false;
	SDL_Event e;
	while (!gameover)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				gameover = true;
				restart = false;
			}
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_p)
				{
					gameover = true;
					restart = true;
				}
				if (e.key.keysym.sym == SDLK_x)
				{
					gameover = true;
					restart = false;
				}

			}
		}
	}
}
void resetgame(vector<bullet>& b1, vector<bullet>& b2, vector<enemy>& e,player&p,vector<hp>&HP)
{
	p.score = 0;
	p.health = 1000;
	p.rect.x = 400;
	p.rect.y = 500;
	e.clear();
	b1.clear();
	b2.clear();
	createbarhp(HP);
}
void renderscore(SDL_Renderer* renderer,TTF_Font*font, player& p) {
	SDL_Color textColor = { 255, 255, 255, 255 };
	string scoreText = "Score: " + to_string(p.score);

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	int textW, textH;
	SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
	SDL_Rect textRect = { 10, 10, textW, textH };

	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);
}
void rendergameover(SDL_Renderer* renderer, TTF_Font* font)
{
	SDL_Color textColor = { 255,255,255,255 };
	string gameovertext = "Ban da cook\nP de choi lai\n X de thoat";
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, gameovertext.c_str(), textColor,200);

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	int textW, textH;
	SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
	SDL_Rect textRect = { (800-textW)/2, (600-textH)/2, textW, textH};

	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);

}

