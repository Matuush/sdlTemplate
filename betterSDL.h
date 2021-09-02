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
    static const SDL_Color defaultColor;
    static const SDL_Rect defaultRect;


    SDL();

    void loop();

private:
    inline void render();
    inline void input(SDL_Event *event);


    inline SDL_Texture* LoadTexture(const char* path);

    void Clear();
	void Display();
	void Destroy();

	void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void SetDrawColor(Uint8 r, Uint8 g, Uint8 b);
    bool isDefaultColor(SDL_Color color);
    bool isDefaultRect(SDL_Rect rect);

	void SetFont(const char* p_font, int size);
	void SetFont(int size);

	void Render(const char* path, SDL_Rect dst, SDL_Rect src, bool flip, SDL_Color color);

	void DrawRectangle(SDL_Rect* rect, SDL_Color color);
    void FillRectangle(SDL_Rect* rect, SDL_Color color);

	void DrawCircle(int p_x, int p_y, int32_t radius, SDL_Color color);
	void FillCircle(int x, int y, int radius, SDL_Color color);

	void DrawLine(int x1, int y1, int x2, int y2, SDL_Color color);
	void DrawPoint(int x, int y, SDL_Color color);

	void DrawText(const char* text, SDL_Rect* rect, SDL_Color color);
};