#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <map>
#include <functional>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define WINDOW_NAME "SDL Template"
const int FRAME_DELAY = 1000 / 60;
SDL_Color current = {0U, 0U, 0U, 255U};

struct SDL {
    int frameStart = 0, frameTime = 0;
    bool running = true;

    SDL_Window* window;
	SDL_Renderer* renderer;

	TTF_Font* font;
	std::map<const char*, SDL_Texture*> textures;

	const int defaultFontSize = 32;
    static const SDL_Color defaultColor;
    static const SDL_Rect defaultRect;

    std::function<void()> render;
    std::function<void(SDL_Event*)> input;


    SDL() {
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0) std::cout << "Error: SDL failed to initialize\nSDL Error: " << SDL_GetError() << "\n";

        window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        if(!window) std::cout << "Error: Failed to open window\nSDL Error: " << SDL_GetError() << "\n";

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer) std::cout << "Error: Failed to create renderer\nSDL Error: " << SDL_GetError() << "\n";

        SDL_SetRenderDrawColor(renderer, current.r, current.g, current.b, current.a);
        
        TTF_Init();
        SetFont("textures/Sans.ttf", defaultFontSize);
    }

    void Loop() {
        while(running){
            Input();
            
            Clear();
            render();
            Display();

            Delay();
        }
    }

    //The library
    inline SDL_Texture* LoadTexture(const char* path) {
        if (textures.count(path) == 0) textures[path] = LoadTexture(path);
        return IMG_LoadTexture(renderer, path);
    }

    inline void Input() {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) running = false;
            input(&event);
        }
    }
    inline void Delay() {
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) SDL_Delay(FRAME_DELAY - frameTime);
        frameStart = SDL_GetTicks();
    }
    
    inline void Clear() {
        SDL_RenderClear(renderer);
    }
	inline void Display() {
        SDL_RenderPresent(renderer);
    }
	void Destroy() {
        SDL_DestroyWindow(window);
    }

	void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        current = {r, g, b, a};
    }
	void SetDrawColor(Uint8 r, Uint8 g, Uint8 b) {
        SDL_SetRenderDrawColor(renderer, r, g, b, current.a);
        current.r = r, current.g = g, current.b = b;
    }
    bool isCurrent(SDL_Color color) {
        return color.r == current.r && 
            color.g == current.g && 
            color.b == current.b &&
            color.a == current.a;
    }
    bool isDefaultRect(SDL_Rect rect){
        return rect.x == defaultRect.x &&
            rect.y == defaultRect.y &&
            rect.w == defaultRect.w &&
            rect.h == defaultRect.h;
    }

	void SetFont(const char* p_font, int size) {
        font = TTF_OpenFont(p_font, size);
        TTF_SetFontOutline(font, size);
    }
	void SetFont(int size) {
        TTF_SetFontOutline(font, size);
    }

	void Render(const char* path, SDL_Rect dst = defaultRect, SDL_Rect src = defaultRect, bool flip = false, SDL_Color color = current) {
        if (textures.count(path) == 0) textures[path] = LoadTexture(path);
        if (!isCurrent(color)) SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_Rect *dstp = isDefaultRect(dst) ? NULL : &dst;
        SDL_Rect *srcp = isDefaultRect(src) ? NULL : &src;
        if (flip) SDL_RenderCopyEx(renderer, textures[path], srcp, dstp, 0, NULL, SDL_FLIP_HORIZONTAL);
        else SDL_RenderCopy(renderer, textures[path], srcp, dstp);
        if (!isCurrent(color)) SDL_SetRenderDrawColor(renderer, current.r, current.g, current.b, current.a);
    }

	void DrawRectangle(SDL_Rect* rect, SDL_Color color = current) {
        if (!isCurrent(color)) SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(renderer, rect);
        if (!isCurrent(color)) SDL_SetRenderDrawColor(renderer, current.r, current.g, current.b, current.a);
    }
    void FillRectangle(SDL_Rect* rect, SDL_Color color = current) {
        if (!isCurrent(color)) SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, rect);
        if (!isCurrent(color)) SDL_SetRenderDrawColor(renderer, current.r, current.g, current.b, current.a);
    }

	void DrawCircle(int p_x, int p_y, int32_t radius, SDL_Color color = current) {
        if (!isCurrent(color)) SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        
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
        if (!isCurrent(color)) SDL_SetRenderDrawColor(renderer, current.r, current.g, current.b, current.a);
    }
	void FillCircle(int x, int y, int radius, SDL_Color color = current) {
        if (!isCurrent(color)) SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

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
        if (!isCurrent(color)) SDL_SetRenderDrawColor(renderer, current.r, current.g, current.b, current.a);
    }

	void DrawLine(int x1, int y1, int x2, int y2, SDL_Color color = current) {
        if (!isCurrent(color)) SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        if (!isCurrent(color)) SDL_SetRenderDrawColor(renderer, current.r, current.g, current.b, current.a);
    }
	void DrawPoint(int x, int y, SDL_Color color = current) {
        if (!isCurrent(color)) SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(renderer, x, y);
        if (!isCurrent(color)) SDL_SetRenderDrawColor(renderer, current.r, current.g, current.b, current.a);
    }

	void DrawText(const char* text, SDL_Rect* rect, SDL_Color color = current) {
        if (!isCurrent(color)) TTF_RenderText_Solid(font, text, color);
        else TTF_RenderText_Solid(font, text, current);
    }
};