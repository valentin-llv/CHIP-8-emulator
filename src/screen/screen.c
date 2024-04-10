#include <SDL.h>

extern SDL_Renderer* renderer;

extern char screen[2048];

void draw(void) {
    for(int j = 0; j < 2048; j++) {
        if(screen[j] == 1) SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        else SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255);

        SDL_Rect rect = { 20 * (j % 64), 20 * ((j - (j % 64)) / 64), 20, 20 };
        SDL_RenderFillRect(renderer, &rect);
    }
}

void clearScreen(void) {
    for(int j = 0; j < 2048; j++) screen[j] = 0;
}