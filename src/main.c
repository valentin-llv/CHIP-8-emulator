#include <stdio.h>
#include <time.h>

#include <SDL.h>

#include "constant/constant.h"

#include "startup/startup.h"

#include "memory/memory.h"
#include "cpu/cpu.h"
#include "screen/screen.h"

#include "events/events.h"

// Window related
SDL_Window* window;
SDL_Renderer* renderer;

// Screen related
char screen[2048];

// Game state infos
char gameRunning;

// Memory related
unsigned char memory[4096];

// CPU related
int pc;

int stack[16];
int sp;

int i;
unsigned char registers[16];

int debug = 0;

// Timer related
int gpTimer;
int soundTimer;

// Keyboard events related
char keyboard[16];

void reset(void) {
    gameRunning = 0;

    // Set CPU reserved pointers to their default value
    pc = 0x200;
    sp = -1;
    i = 0;

    // Reset timers to 0
    gpTimer = 0;
    soundTimer = 0;

    // Reset stack values and registers values
    for(int j = 0; j < 16; j++) stack[j] = 0;
    for(int j = 0; j < 16; j++) registers[j] = 0;

    // Reset mem
    for(int j = 0; j < 4096; j++) memory[j] = 0;

    // Reset keyboard
    for(int j = 0; j < 16; j++) keyboard[j] = 0;

    // Fill the reserved memory with font data
    fillReservedMemory();
}

int lastFrameTime = 0;
int instructionsCycleCount = 0;
void loop(void) {
    while(gameRunning) {
        int delta_time = SDL_GetTicks() - lastFrameTime;

        if(instructionsCycleCount < INSTRUCTIONS_PER_CYCLE) {
            listenEvents();
            execOpcode(getOpcode());
            draw();

            if(soundTimer > 0) soundTimer -= 1;
            if(gpTimer > 0) gpTimer -= 1;

            SDL_RenderPresent(renderer);

            instructionsCycleCount ++;
        } else if(delta_time > 16.6) {
            instructionsCycleCount = 0;
            // Store the milliseconds of the current frame to be used in the next one
            lastFrameTime = SDL_GetTicks();
        }
    }
}

int WinMain(int argc, char* argv[]) {
    // Init the random function with seed
    srand(time(NULL));

    // Init SDL
    initSDL();

    // Create window and renderer
    window = createWindow("CHIP-8 emulator", WINDOW_WIDTH, WINDOW_HEIGHT);
    renderer = createRenderer(window);

    // Reset memory and vars
    reset();

    // Load ame file into memory
    loadFileIntoMem("games/TEST_ROM3");

    // Start game loop
    gameRunning = 1;
    loop();

    // Clean exit of SDL
    quitSDL();

    return 0;
}