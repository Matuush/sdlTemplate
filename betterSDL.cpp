#include "betterSDL.h"

const SDL_Color SDL::defaultColor = {2, 2, 2, 2};
const SDL_Rect SDL::defaultRect = {0, 0, 0, 0};

SDL::SDL() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) std::cout << "Error: SDL failed to initialize\nSDL Error: " << SDL_GetError() << "\n";

    SDL_Window *window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(!window) std::cout << "Error: Failed to open window\nSDL Error: " << SDL_GetError() << "\n";

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) std::cout << "Error: Failed to create renderer\nSDL Error: " << SDL_GetError() << "\n";

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    std::cout << "prdel";
    TTF_Init();
    font = TTF_OpenFont("default/defaultFont.ttf", defaultFontSize);
}

void SDL::loop() {
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


void SDL::render() {

}

void SDL::input(SDL_Event *event) {

}



void SDL::Clear() {
    SDL_RenderClear(renderer);
}

void SDL::Display() {
    SDL_RenderPresent(renderer);
}

void SDL::Destroy() {
    SDL_DestroyWindow(window);
}
void SDL::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void SDL::SetDrawColor(Uint8 r, Uint8 g, Uint8 b) {
    Uint8 *a, *h, *j, *k;
    SDL_GetRenderDrawColor(renderer, h, j, k, a);
    SDL_SetRenderDrawColor(renderer, r, g, b, *a);
}

bool SDL::isDefaultColor(SDL_Color color) {
    return color.r == defaultColor.r && 
        color.g == defaultColor.g && 
        color.b == defaultColor.b &&
        color.a == defaultColor.a;
}

bool SDL::isDefaultRect(SDL_Rect rect){
    return rect.x == defaultRect.x &&
        rect.y == defaultRect.y &&
        rect.w == defaultRect.w &&
        rect.h == defaultRect.h;
}

void SDL::SetFont(const char* p_font, int size) {
    font = TTF_OpenFont(p_font, size);
}

void SDL::SetFont(int size) {
    TTF_SetFontOutline(font, size);
}

SDL_Texture* SDL::LoadTexture(const char* path) {
	if (textures.count(path) == 0) textures[path] = LoadTexture(path);
	return IMG_LoadTexture(renderer, path);
}

void SDL::Render(const char* path, SDL_Rect dst = defaultRect, SDL_Rect src = defaultRect, bool flip = false, SDL_Color color = defaultColor) {
    if (textures.count(path) == 0) textures[path] = LoadTexture(path);
    Uint8 *r, *g, *b, *a;
    if (isDefaultColor(color)) {
        SDL_GetRenderDrawColor(renderer, r, g, b, a);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }
    SDL_Rect *dstp = isDefaultRect(dst) ? NULL : &dst;
    SDL_Rect *srcp = isDefaultRect(src) ? NULL : &src;
    if (flip) SDL_RenderCopyEx(renderer, textures[path], srcp, dstp, 0, NULL, SDL_FLIP_HORIZONTAL);
    else SDL_RenderCopy(renderer, textures[path], srcp, dstp);
    if (!isDefaultColor(color)) SDL_SetRenderDrawColor(renderer, *r, *g, *b, *a);
}

void SDL::DrawRectangle(SDL_Rect* rect, SDL_Color color = defaultColor) {
    Uint8* r, *g, *b, *a;
    if (!isDefaultColor(color)) {
        SDL_GetRenderDrawColor(renderer, r, g, b, a);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }
    SDL_RenderDrawRect(renderer, rect);
    if (!isDefaultColor(color)) SDL_SetRenderDrawColor(renderer, *r, *g, *b, *a);
}
void SDL::FillRectangle(SDL_Rect* rect, SDL_Color color = defaultColor) {
    Uint8 *r, *g, *b, *a;
    if (!isDefaultColor(color)) {
        SDL_GetRenderDrawColor(renderer, r, g, b, a);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }
    SDL_RenderFillRect(renderer, rect);
    if (!isDefaultColor(color)) SDL_SetRenderDrawColor(renderer, *r, *g, *b, *a);
}

void SDL::DrawCircle(int p_x, int p_y, int32_t radius, SDL_Color color = defaultColor) {
    Uint8 *r, *g, *b, *a;
    if (!isDefaultColor(color)) {
        SDL_GetRenderDrawColor(renderer, r, g, b, a);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }
    
    const int32_t diameter = (radius * 2);
    int32_t x = (radius - 1), y = 0;
    int32_t tx = 1, ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y) {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, p_x + x, p_y - y);
        SDL_RenderDrawPoint(renderer, p_x + x, p_y + y);
        SDL_RenderDrawPoint(renderer, p_x - x, p_y - y);
        SDL_RenderDrawPoint(renderer, p_x - x, p_y + y);
        SDL_RenderDrawPoint(renderer, p_x + y, p_y - x);
        SDL_RenderDrawPoint(renderer, p_x + y, p_y + x);
        SDL_RenderDrawPoint(renderer, p_x - y, p_y - x);
        SDL_RenderDrawPoint(renderer, p_x - y, p_y + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }

        else {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
    if (!isDefaultColor(color)) SDL_SetRenderDrawColor(renderer, *r, *g, *b, *a);
}
void SDL::FillCircle(int x, int y, int radius, SDL_Color color = defaultColor) {
    Uint8 *r, *g, *b, *a;
    if (!isDefaultColor(color)) {
        SDL_GetRenderDrawColor(renderer, r, g, b, a);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }

    int offsetx = 0, offsety = radius, d = radius - 1;
    int status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
            x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
            x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
            x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
            x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
    if (!isDefaultColor(color)) SDL_SetRenderDrawColor(renderer, *r, *g, *b, *a);
}

void SDL::DrawLine(int x1, int y1, int x2, int y2, SDL_Color color = defaultColor) {
    Uint8 *r, *g, *b, *a;
    if (!isDefaultColor(color)) {
        SDL_GetRenderDrawColor(renderer, r, g, b, a);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    if (!isDefaultColor(color)) SDL_SetRenderDrawColor(renderer, *r, *g, *b, *a);
}
void SDL::DrawPoint(int x, int y, SDL_Color color = defaultColor) {
    Uint8 *r, *g, *b, *a;
    if (!isDefaultColor(color)) {
        SDL_GetRenderDrawColor(renderer, r, g, b, a);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }
    SDL_RenderDrawPoint(renderer, x, y);
    if (!isDefaultColor(color)) SDL_SetRenderDrawColor(renderer, *r, *g, *b, *a);
}

void SDL::DrawText(const char* text, SDL_Rect* rect, SDL_Color color = defaultColor) {
    Uint8 *r, *g, *b, *a;
    SDL_GetRenderDrawColor(renderer, r, g, b, a);
    if (!isDefaultColor(color)) TTF_RenderText_Solid(font, text, color);
    else TTF_RenderText_Solid(font, text, color);
}