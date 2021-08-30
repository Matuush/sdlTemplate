#include <SDL2/SDL.h>
#include <iostream>

#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 720
#define WINDOW_NAME "SDL Template"
#define FRAME_DELAY 18

int main(int argc, char** argv){
    if(SDL_Init(SDL_INIT_VIDEO) < 0) std::cout << "Error: SDL failed to initialize\nSDL Error: " << SDL_GetError() << "\n";

    SDL_Window *window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(!window) std::cout << "Error: Failed to open window\nSDL Error: " << SDL_GetError() << "\n";

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) std::cout << "Error: Failed to create renderer\nSDL Error: " << SDL_GetError() << "\n";
    
    int frameStart = 0;
    bool running = true;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) running = false;

        }

        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
        
        int frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < FRAME_DELAY) SDL_Delay(FRAME_DELAY - frameTime);
		frameStart = SDL_GetTicks();
    }

    return 0;
}
