﻿#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<string>
#include"game.h"
#include"bullets.h"
#include"Boss.h"
#include"barHP.h"
#include<fstream>
#include<SDL_mixer.h>
using namespace std;
Animation victoryAnim;
vector<SDL_Texture*> winFrames;
bool victoryStarted = false;
int backgroundY = 0; 
Uint8* audioBuffer;
Uint32 audioLength;

void startgame(SDL_Renderer* renderer, bool& gamestart)
{
	bool menugame = false;
	SDL_Event e;
	while (!gamestart)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				gamestart = true;
				menugame = true;
			}
		}
	}
}void renderstartgame(SDL_Renderer* renderer, SDL_Texture* startTexture)
{
	SDL_Rect startRect = { 0, 0, 800, 600 };
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, startTexture, NULL, &startRect);
	SDL_RenderPresent(renderer);
}
void endgame(SDL_Renderer* renderer, bool& restart) {
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
void renderendgame(SDL_Renderer* renderer, SDL_Texture* endTexture)
{
	SDL_Rect endRect=  { 0, 0, 800, 600 };
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, endTexture, NULL, &endRect);
	SDL_RenderPresent(renderer);
}
void resetgame(vector<bullet>& b1, vector<bullet>& b2, vector<enemy>& e,player&p,vector<hp>&HP,vector<bullet>&b3,Boss&boss,bool&bossSpawned,vector<combo>&cb)
{
	p.combo = 0;
	if (p.score >= p.highscore)
	{
		p.highscore = p.score;
		p.score = 0;
	}
	else
	{
		p.score = 0;
	}

	p.health = 1000;
	p.rect.x = 400;
	p.rect.y = 500;
	e.clear();
	b1.clear();
	b2.clear();
	b3.clear();
	cb.clear();
	boss.health = 5000;
	boss.distance = -50;
	boss.bombs.clear();
	boss.bullets.clear();
	 bossSpawned = false;
	createbarhp(HP);
}
void renderscore(SDL_Renderer* renderer,TTF_Font*font, player& p) {
	SDL_Color textColor = { 255, 255, 255, 255 };
	string scoreText = "Score: " + to_string(p.score);
	string highscoreText = "High Score: " + to_string(p.highscore);

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
	SDL_Surface* txSurface = TTF_RenderText_Solid(font, highscoreText.c_str(), textColor);

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Texture* txTexture = SDL_CreateTextureFromSurface(renderer, txSurface);

	int textW, textH;
	SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
	SDL_Rect textRect = { 10, 10, textW, textH };
	SDL_QueryTexture(txTexture, NULL, NULL, &textW, &textH);
	SDL_Rect txRect = { 10, 40, textW, textH };

	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);

	SDL_RenderCopy(renderer, txTexture, NULL, &txRect);
	SDL_DestroyTexture(txTexture);
}


void renderBackground(SDL_Renderer* renderer, SDL_Texture* backgroundTexture) {
	backgroundY += 1;
	if (backgroundY >= 600)
		backgroundY = 0;

	SDL_Rect bg1 = { 0, backgroundY, 800, 600 };
	SDL_Rect bg2 = { 0, backgroundY - 600, 800, 600 };

	SDL_RenderCopy(renderer, backgroundTexture, NULL, &bg1);
	SDL_RenderCopy(renderer, backgroundTexture, NULL, &bg2);
}


void loadVictoryAnim(SDL_Renderer* renderer) {
	for (int i = 0; i <74; ++i) {
		char filename[64];
		sprintf_s(filename, "asset/win_e_%02d.png", i);
		SDL_Texture* frame = IMG_LoadTexture(renderer, filename);
		victoryAnim.addFrame(frame);
	}
	victoryAnim.setFrameDelay(5);
	victoryAnim.setLoop(false);
}

void renderWingame(SDL_Renderer* renderer)
{
	
	victoryAnim.update();
	SDL_Texture* currentFrame = victoryAnim.getCurrentFrame();
	if (currentFrame) {
		SDL_Rect dst = { 0,0,800,600 };
		SDL_RenderCopy(renderer, currentFrame, nullptr, &dst);
	}
}
