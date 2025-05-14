#include<iostream>
#include<SDL.h>
#include<SDL_Rect.h>
#include"player.h"
#include"enemies.h"
#include"bullets.h"
#include"game.h"
#include"barHP.h"
#include"Boss.h"
#include"Animation.h"
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
using namespace std;

int main(int argc, char* agv[])
{
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	TTF_Init();
	Mix_OpenAudio(22050, AUDIO_S16LSB, 2, 4096);
	IMG_Init(IMG_INIT_PNG);
	TTF_Font* font = TTF_OpenFont("asset/Retro Gaming.ttf", 24);
	SDL_Color textColor = { 255, 255, 255, 255 };

	SDL_Window* window = SDL_CreateWindow("Space shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	Mix_Chunk* shootSound = Mix_LoadWAV("asset/shootSound.wav");
	Mix_Chunk* bombSound = Mix_LoadWAV("asset/bombSound.wav");
	Mix_Chunk* victorySound = Mix_LoadWAV("asset/victory.wav");

	SDL_Texture* enemiesTexture = IMG_LoadTexture(renderer, "asset/enemies.png");
	SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, "asset/background.jpg");
	SDL_Texture* bulletsTexture = IMG_LoadTexture(renderer, "asset/bullets.png");
	SDL_Texture* bulletsETexture = IMG_LoadTexture(renderer, "asset/bulletsE.png");
	SDL_Texture* bulletsBossTexture = IMG_LoadTexture(renderer, "asset/bulletsBoss.png");
	SDL_Texture* startTexture = IMG_LoadTexture(renderer, "asset/start screen.jpg");
	SDL_Texture* endTexture = IMG_LoadTexture(renderer, "asset/game_over.png");
	SDL_Texture* bombTexture = IMG_LoadTexture(renderer, "asset/bomb.png");
	SDL_Texture* nuclearbombTexture = IMG_LoadTexture(renderer, "asset/nuclearbomb.png");
	SDL_Texture* bossTexture = IMG_LoadTexture(renderer, "asset/boss.png");
	SDL_Texture* engine1 = IMG_LoadTexture(renderer, "asset/engine1.png");
	SDL_Texture* engine2 = IMG_LoadTexture(renderer, "asset/engine2.png");
	SDL_Texture* engine3 = IMG_LoadTexture(renderer, "asset/engine3.png");


	player p;
	createplayer(p);
	p.engine.addFrame(engine1);
	p.engine.addFrame(engine2);
	p.engine.addFrame(engine3);
	renderstartgame(renderer, startTexture);
	bool running = true;
	bool gameover = false;
	SDL_Event event;
	Boss boss;
	vector<enemy>e;
	vector<bullet>b1;
	vector<bullet>b2;
	vector<bullet>b3;
	vector<hp>HP;
	vector<hp>HPboss;
	vector<combo>cb;
	createbarhp(HP);
	createplayer(p);
	bool gamestart = false;
	bool victoryAnimLoaded = false;
	bool victoryloadSound = false;
	Animation victoryAnim;
	startgame(renderer, gamestart);
	Uint32 lastTime = SDL_GetTicks();

	bool bossSpawned = false;
	while (running)
	{

		Uint32 currentTime = SDL_GetTicks();
		float Time = (currentTime - lastTime) / 1500.0;
		lastTime = currentTime;

		SDL_PumpEvents();
		const Uint8* keystates = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			controlplayer(p, event, keystates, Time);
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
			{
				createplayerbullet(b1, p);
				Mix_PlayChannel(-1, shootSound, 0);
			}
			if (p.combo >= 50)
			{
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
				{
					createnuclearbomb(b3, p);
					p.combo = 0;
					createbarcombo(cb, p);
				}
			}

		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		renderBackground(renderer, backgroundTexture);

		updateplayer(p);
		renderplayer(p, renderer);
		p.engine.update();
		p.engine.render(renderer, p.rect.x, p.rect.y);
		if (!bossSpawned)
		{
			spawnenemy(e, p);
			createenemiesbullet(b2, e, p);
		}

		updateEnemies(e, p,b2);
		renderEnemies(e, renderer, enemiesTexture);
		updateplayerbullet(b1);
		updateenemiesbullet(b2);
		updatenuclearbomb(b3);
		renderplayerbullet(b1, renderer, bulletsTexture);
		renderenemiesbullet(b2, renderer,bulletsETexture);
		rendernuclearbomb(b3, renderer,nuclearbombTexture);
		checkcollision1(b1, e, p, cb, renderer);
		checkcollision2(b2, p, HP, cb);
		nuclearbombexplode(b3, e, p, b2, renderer,bombSound);
		checkcollisionEandP(e, p, HP, renderer);
		checkcollisionEnemies(e, renderer);
		renderbarhp(renderer, HP);


		SDL_Delay(16);
		if (p.health == 0)
		{
			bool restart = false;
			renderendgame(renderer, endTexture);
			SDL_RenderPresent(renderer);
			endgame(renderer, restart);
			if (restart)
			{
				resetgame(b1, b2, e, p, HP, b3, boss, bossSpawned, cb);

			}
			else
			{
				running = false;
				gameover = true;

			}
		}

		if (p.score >= 2000 && !bossSpawned)
		{
			initBoss(boss);
			createHPboss(HPboss);
			bossSpawned = true;
			e.clear();
			b2.clear();
			cb.clear();
		}

		renderscore(renderer, font, p);
		renderbarcombo(renderer, cb);


		if (!victoryAnimLoaded) {
			loadVictoryAnim(renderer);
			victoryAnimLoaded = true; 
		}

		if (bossSpawned)
		{
			updateBoss(boss, p, HP);
			renderBoss(boss, renderer, bombTexture, bossTexture,bulletsBossTexture);
			renderHPboss(renderer, HPboss);
			checkcolisionboss(b1, boss,HPboss);
			 
			if (boss.health <= 0)
			{
				
					if (!victoryloadSound)
					{
						Mix_PlayChannel(-1, victorySound, 0);
						victoryloadSound = true;
					}
					bool animationDone = false;
					while (!animationDone)
					{
						SDL_Event e;
						while (SDL_PollEvent(&e)) {
							if (e.type == SDL_QUIT) {
								animationDone = true;
								running = false;
							}
						}

						SDL_RenderClear(renderer);
						renderWingame(renderer);
						SDL_RenderPresent(renderer);
						SDL_Delay(150); 
						if (victoryAnim.isFinished()) {
							animationDone = true;
						}
					}

			}
				
		}


		if (cb.size() == 10)
		{
			renderbarcombofull(renderer, cb);
		}
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(enemiesTexture);
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(bulletsTexture);
	SDL_DestroyTexture(bulletsETexture);
	SDL_DestroyTexture(bulletsBossTexture);
	SDL_DestroyTexture(startTexture);
	SDL_DestroyTexture(endTexture);
	SDL_DestroyTexture(bombTexture);
	SDL_DestroyTexture(nuclearbombTexture);
	SDL_DestroyTexture(bossTexture);
	SDL_DestroyTexture(engine1);
	SDL_DestroyTexture(engine2);
	SDL_DestroyTexture(engine3);
	Mix_FreeChunk(shootSound);
	Mix_FreeChunk(bombSound);
	Mix_FreeChunk(victorySound);
	Mix_CloseAudio();
	SDL_Quit();
	TTF_CloseFont(font);
	TTF_Quit();
	return 0;
}