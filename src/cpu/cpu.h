#include <SDL.h>

#ifndef cpu_h
#define cpu_h

extern unsigned char memory[4096];

extern int pc;
extern int stack[16];
extern int sp;
extern unsigned char registers[16];
extern int i;

extern int gpTimer;
extern int soundTimer;

extern char keyboard[16];

extern SDL_Renderer* renderer;

int getOpcode(void);

void execOpcode(int opcode);

#endif