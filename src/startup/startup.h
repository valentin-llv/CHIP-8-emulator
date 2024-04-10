#include "SDL.h"

#ifndef startup_h
#define startup_h

void initSDL(void);
SDL_Window* createWindow(char* title, int width, int height);
SDL_Renderer* createRenderer(SDL_Window* window);

void quitSDL();    

#endif