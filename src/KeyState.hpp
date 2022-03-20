#pragma once
#include "Vector2D.hpp"
#include "SDL2/SDL.h"

struct KeyState {
	bool w = 0, s = 0, a = 0, d = 0;
	bool num[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	KeyState() = default;
	void zeroify() {
		w = 0, s = 0, a = 0, d = 0;
		for(bool n : num) n = 0;
	}
	void update(SDL_Event* event){
		switch (event->type) {
			case SDL_KEYDOWN:
				switch (event->key.keysym.sym) {
					case SDLK_w: w = 1; break;
					case SDLK_a: a = 1; break;
					case SDLK_s: s = 1; break;
					case SDLK_d: d = 1; break;
					case SDLK_1: num[0] = 1; break;
					case SDLK_2: num[1] = 1; break;
					case SDLK_3: num[2] = 1; break;
					case SDLK_4: num[3] = 1; break;
					case SDLK_5: num[4] = 1; break;
					case SDLK_6: num[5] = 1; break;
					case SDLK_7: num[6] = 1; break;
					case SDLK_8: num[7] = 1; break;
					case SDLK_9: num[8] = 1; break;
					case SDLK_0: num[9] = 1; break;

				}
				break;
			case SDL_KEYUP:
				switch (event->key.keysym.sym) {
					case SDLK_w: w = 0; break;
					case SDLK_a: a = 0; break;
					case SDLK_s: s = 0; break;
					case SDLK_d: d = 0; break;
					case SDLK_1: num[0] = 0; break;
					case SDLK_2: num[1] = 0; break;
					case SDLK_3: num[2] = 0; break;
					case SDLK_4: num[3] = 0; break;
					case SDLK_5: num[4] = 0; break;
					case SDLK_6: num[5] = 0; break;
					case SDLK_7: num[6] = 0; break;
					case SDLK_8: num[7] = 0; break;
					case SDLK_9: num[8] = 0; break;
					case SDLK_0: num[9] = 0; break;
				}
			break;
		}
	}
};