#include<iostream>
#include<SDL.h>
#include"thoatgame.h"
#include"bullets.h"
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
				if (e.key.keysym.sym == SDLK_r)
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