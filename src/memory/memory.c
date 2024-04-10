#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

extern unsigned char memory[4096];

void loadFileIntoMem(char romTitle[]) {
    FILE* gameFile = fopen(romTitle, "rb");

    if(!gameFile) {
        printf("Error openning game file !");
        exit(4);
    }

    fseek(gameFile, 0, SEEK_END);
    int fileSize = ftell(gameFile);
    fseek(gameFile, 0, SEEK_SET);

    // Clear memory
    for(int j = 0; j < 4096; j++) memory[j] = 0;

    int j = 0x200;
    unsigned char value;
    while(j < fileSize + 0x200) {
        fread(&value, 1, 1, gameFile);
        memory[j] = value;
        j ++;
    }

    fclose(gameFile);
}

void fillReservedMemory(void) {
    int j = 0; // 0
    memory[j + 0] = 0xF0;
    memory[j + 1] = 0x90;
    memory[j + 2] = 0x90;
    memory[j + 4] = 0x90;
    memory[j + 5] = 0xF0;

    j = 0x6 * 1; // 1
    memory[j + 0] = 0x20;
    memory[j + 1] = 0x60;
    memory[j + 2] = 0x20;
    memory[j + 4] = 0x20;
    memory[j + 5] = 0x70;

    j = 0x6 * 2; // 2
    memory[j + 0] = 0xF0;
    memory[j + 1] = 0x10;
    memory[j + 2] = 0xF0;
    memory[j + 4] = 0x80;
    memory[j + 5] = 0xF0;

    j = 0x6 * 3; // 3
    memory[j + 0] = 0xF0;
    memory[j + 1] = 0x10;
    memory[j + 2] = 0xF0;
    memory[j + 4] = 0x10;
    memory[j + 5] = 0xF0;

    j = 0x6 * 4; // 4
    memory[j + 0] = 0x90;
    memory[j + 1] = 0x90;
    memory[j + 2] = 0xF0;
    memory[j + 4] = 0x10;
    memory[j + 5] = 0x10;

    j = 0x6 * 5; // 5
    memory[j + 0] = 0xF0;
    memory[j + 1] = 0x80;
    memory[j + 2] = 0xF0;
    memory[j + 4] = 0x10;
    memory[j + 5] = 0xF0;

    j = 0x6 * 6; // 6
    memory[j + 0] = 0xF0;
    memory[j + 1] = 0x80;
    memory[j + 2] = 0xF0;
    memory[j + 4] = 0x90;
    memory[j + 5] = 0xF0;

    j = 0x6 * 7; // 7
    memory[j + 0] = 0xF0;
    memory[j + 1] = 0x10;
    memory[j + 2] = 0x20;
    memory[j + 4] = 0x40;
    memory[j + 5] = 0x40;

    j = 0x6 * 8; // 8
    memory[j + 0] = 0xF0;
    memory[j + 1] = 0x90;
    memory[j + 2] = 0xF0;
    memory[j + 4] = 0x90;
    memory[j + 5] = 0xF0;

    j = 0x6 * 9; // 9
    memory[j + 0] = 0xF0;
    memory[j + 1] = 0x90;
    memory[j + 2] = 0xF0;
    memory[j + 4] = 0x10;
    memory[j + 5] = 0xF0;

    j = 0x6 * 10; // A
    memory[j + 0] = 0xF0;
    memory[j + 1] = 0x90;
    memory[j + 2] = 0xF0;
    memory[j + 4] = 0x90;
    memory[j + 5] = 0x90;

    j = 0x6 * 11; // B
    memory[j + 0] = 0xE0;
    memory[j + 1] = 0x90;
    memory[j + 2] = 0xE0;
    memory[j + 4] = 0x90;
    memory[j + 5] = 0xE0;

    j = 0x6 * 12; // C
    memory[j + 0] = 0xF0;
    memory[j + 1] = 0x80;
    memory[j + 2] = 0x80;
    memory[j + 4] = 0x80;
    memory[j + 5] = 0xF0;

    j = 0x6 * 13; // D
    memory[j + 0] = 0xE0;
    memory[j + 1] = 0x90;
    memory[j + 2] = 0x90;
    memory[j + 4] = 0x90;
    memory[j + 5] = 0xE0;

    j = 0x6 * 14; // E
    memory[j + 0] = 0xF0;
    memory[j + 1] = 0x80;
    memory[j + 2] = 0xF0;
    memory[j + 4] = 0x80;
    memory[j + 5] = 0xF0;

    j = 0x6 * 15; // F
    memory[j + 0] = 0xF0;
    memory[j + 1] = 0x80;
    memory[j + 2] = 0xF0;
    memory[j + 4] = 0x80;
    memory[j + 5] = 0x80;
}