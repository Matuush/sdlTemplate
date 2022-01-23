#include "betterSDL.h"

SDL interface;

int main(int argc, char** argv){
    interface.setInput([&](SDL_Event*){});
    interface.setUpdate([&](){});
    interface.setRender([&](){
        interface.FillCircle(100, 100, 30, {255, 0, 0, 0});
    });
    
    interface.SetDrawColor(0, 0, 0);
    interface.loop();

    return 0;
}