#include "betterSDL.h"

const SDL_Color SDL::defaultColor = {2, 3, 2, 2};
const SDL_Rect SDL::defaultRect = {0, 0, 0, 0};

int main(int argc, char** argv){
    SDL interface;

    SDL_Rect rect{100, 100, 200, 200};

    interface.render = [&](){
        interface.FillRectangle(&rect, {0, 255, 0, 0});
    };
    interface.input = [&](SDL_Event* event){

    };

    interface.Loop();

    interface.Destroy();

    return 0;
}