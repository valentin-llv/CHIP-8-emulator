#include <stdio.h>
#include "SDL.h"

#include "startup.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;

void initSDL(void) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        exit(0);
    }
}

SDL_Window* createWindow(char* title, int width, int height) {
    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);

    if(!window) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();

        exit(0);
    }

    return window;
}

SDL_Renderer* createRenderer(SDL_Window* window) {
    Uint32 renderFlags = SDL_RENDERER_ACCELERATED;

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, renderFlags);
    if(!renderer) {
        printf("Error creating renderer: %s\n", SDL_GetError());

        SDL_DestroyWindow(window);
        SDL_Quit();

        exit(0);
    }

    return renderer;
}

void quitSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}