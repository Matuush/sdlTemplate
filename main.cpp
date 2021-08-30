#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <map>

#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 720
#define WINDOW_NAME "SDL Template"
const int FRAME_DELAY = 1000 / 60;

struct SDL {
    int frameStart = 0;
    bool running = true;
    SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	std::map<const char*, SDL_Texture*> textures;
	const int defaultFontSize = 32;

    SDL() {
        if(SDL_Init(SDL_INIT_VIDEO) < 0) std::cout << "Error: SDL failed to initialize\nSDL Error: " << SDL_GetError() << "\n";

        SDL_Window *window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        if(!window) std::cout << "Error: Failed to open window\nSDL Error: " << SDL_GetError() << "\n";

        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer) std::cout << "Error: Failed to create renderer\nSDL Error: " << SDL_GetError() << "\n";
    }

    void loop() {
        while(running){
            SDL_Event event;
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT) running = false;
                input(&event);
            }

            SDL_RenderClear(renderer);
            
            render();

            SDL_RenderPresent(renderer);
            
            int frameTime = SDL_GetTicks() - frameStart;
            if (frameTime < FRAME_DELAY) SDL_Delay(FRAME_DELAY - frameTime);
            frameStart = SDL_GetTicks();
        }
    }

private:
    inline void render() {

    }

    inline void input(SDL_Event *event) {

    }
};

int main(int argc, char** argv){
    SDL interface;
    
    interface.loop();

    return 0;
}
