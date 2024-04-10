#include <SDL.h>

#include "events.h"

SDL_Event event;

extern char keyboard[16];

void listenEvents(void) {
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_KEYDOWN) {
            // Quit event
            if(event.type == SDL_QUIT) gameRunning = 0;
            if(event.key.keysym.sym == SDLK_ESCAPE) gameRunning = 0;

            if(event.key.keysym.sym == SDLK_1) keyboard[1] = 1;
            if(event.key.keysym.sym == SDLK_q) keyboard[4] = 1;
            if(event.key.keysym.sym == SDLK_a) keyboard[7] = 1;
            if(event.key.keysym.sym == SDLK_z) keyboard[0xA] = 1;

            if(event.key.keysym.sym == SDLK_2) keyboard[2] = 1;
            if(event.key.keysym.sym == SDLK_w) keyboard[5] = 1;
            if(event.key.keysym.sym == SDLK_s) keyboard[8] = 1;
            if(event.key.keysym.sym == SDLK_x) keyboard[0] = 1;

            if(event.key.keysym.sym == SDLK_3) keyboard[3] = 1;
            if(event.key.keysym.sym == SDLK_e) keyboard[6] = 1;
            if(event.key.keysym.sym == SDLK_d) keyboard[9] = 1;
            if(event.key.keysym.sym == SDLK_c) keyboard[0xB] = 1;

            if(event.key.keysym.sym == SDLK_4) keyboard[0xC] = 1;
            if(event.key.keysym.sym == SDLK_r) keyboard[0xD] = 1;
            if(event.key.keysym.sym == SDLK_f) keyboard[0xE] = 1;
            if(event.key.keysym.sym == SDLK_v) keyboard[0xF] = 1;
        }

        if(event.type == SDL_KEYUP) {
            if(event.key.keysym.sym == SDLK_1) keyboard[1] = 0;
            if(event.key.keysym.sym == SDLK_q) keyboard[4] = 0;
            if(event.key.keysym.sym == SDLK_a) keyboard[7] = 0;
            if(event.key.keysym.sym == SDLK_z) keyboard[0xA] = 0;

            if(event.key.keysym.sym == SDLK_2) keyboard[2] = 0;
            if(event.key.keysym.sym == SDLK_w) keyboard[5] = 0;
            if(event.key.keysym.sym == SDLK_s) keyboard[8] = 0;
            if(event.key.keysym.sym == SDLK_x) keyboard[0] = 0;

            if(event.key.keysym.sym == SDLK_3) keyboard[3] = 0;
            if(event.key.keysym.sym == SDLK_e) keyboard[6] = 0;
            if(event.key.keysym.sym == SDLK_d) keyboard[9] = 0;
            if(event.key.keysym.sym == SDLK_c) keyboard[0xB] = 0;

            if(event.key.keysym.sym == SDLK_4) keyboard[0xC] = 0;
            if(event.key.keysym.sym == SDLK_r) keyboard[0xD] = 0;
            if(event.key.keysym.sym == SDLK_f) keyboard[0xE] = 0;
            if(event.key.keysym.sym == SDLK_v) keyboard[0xF] = 0;
        }
    }
}

void resetKeyboard(void) {
    for(int j = 0; j < 16; j++) keyboard[j] = 0;
}