#include "betterSDL.h"

const SDL_Color SDL::defaultColor = {2, 2, 2, 2};
const SDL_Rect SDL::defaultRect = {0, 0, 0, 0};

int main(int argc, char** argv){
    SDL interface;
    
    interface.loop();

    return 0;
}