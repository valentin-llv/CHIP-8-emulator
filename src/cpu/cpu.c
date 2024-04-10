#include <stdio.h>

#include "cpu.h"
#include "../screen/screen.h"

#include "../utils/utils.h"

extern char screen[2048];

extern int debug;

int getOpcode(void) {
    if(pc >= 4094) {
        printf("Outside of memory bound");
        exit(0);
    }

    if(debug) printf("%x\n", (memory[pc] << 8) + memory[pc + 1]);

    return (memory[pc] << 8) + memory[pc + 1];
}

void execOpcode(int opcode) {
    unsigned char instructionType = (opcode >> 12);
    unsigned char x = (opcode >> 8) & 0b1111;
    unsigned char y = (opcode >> 4) & 0b1111;
    unsigned char instructionSubType = opcode & 0b1111;

    int lastPC = pc;
    char wait = 0;

    // 0x0 type
    if(opcode == 0x00E0) clearScreen();
    if(opcode == 0x00EE) {
        pc = stack[sp];
        sp -= 1;
    }

    // 0x1 type
    if(instructionType == 0x1) pc = (x << 8) + (y << 4) + instructionSubType;

    // 0x2 type
    if(instructionType == 0x2) {
        sp ++;
        stack[sp] = pc + 2;

        pc = (x << 8) + (y << 4) + instructionSubType;
    }

    // 0x3 type
    if(instructionType == 0x3) {
        if(registers[x] == (y << 4) + instructionSubType) pc += 4;
    }

    // 0x4 type
    if(instructionType == 0x4) {
        if(registers[x] != (y << 4) + instructionSubType) pc += 4;
    }

    // 0x5 type
    if(instructionType == 0x5) {
        if(registers[x] == registers[y]) pc += 4;
    }

    // 0x6 type
    if(instructionType == 0x6) registers[x] = (y << 4) + instructionSubType;

    // 0x7 type
    if(instructionType == 0x7) registers[x] = registers[x] + (y << 4) + instructionSubType;

    // 0x8 type
    if(instructionType == 0x8) {
        if(instructionSubType == 0x0) registers[x] = registers[y];
        if(instructionSubType == 0x1) registers[x] = registers[x] | registers[y];
        if(instructionSubType == 0x2) registers[x] = registers[x] & registers[y];
        if(instructionSubType == 0x3) registers[x] = registers[x] ^ registers[y];
        if(instructionSubType == 0x4) {
            registers[x] += registers[y];

            if(registers[x] < registers[y]) registers[15] = 1;
            else registers[15] = 0;
        }
        if(instructionSubType == 0x5) {
            if(registers[x] > registers[y]) registers[15] = 1;
            else registers[15] = 0;

            registers[x] -= registers[y];
        }
        if(instructionSubType == 0x6) {
            if(registers[x] & 0b1 == 1) registers[15] = 1;
            else registers[15] = 0;

            registers[x] >>= 1;
        }
        if(instructionSubType == 0x7) {
            if(registers[x] < registers[y]) registers[15] = 1;
            else registers[15] = 0;

            registers[x] = registers[y] - registers[x];
        }
        if(instructionSubType == 0xE) {
            if((registers[x] >> 7) == 1) registers[15] = 1;
            else registers[15] = 0;

            registers[x] <<= 1;
        }
    }

    // 0x9 type
    if(instructionType == 0x9) {
        if(registers[x] != registers[y]) pc += 4;
    }

    // 0xA type
    if(instructionType == 0xA) i = (x << 8) + (y << 4) + instructionSubType;

    // 0xB type
    if(instructionType == 0xB) pc = (x << 8) + (y << 4) + instructionSubType + registers[0];

    // 0xC type
    if(instructionType == 0xC) registers[x] = randimInt(0, 255) & ((y << 4) + instructionSubType);

    // 0xD type
    if(instructionType == 0xD) {
        registers[15] = 0;

        for(int j = 0; j < instructionSubType; j++) {
            for(int l = 0; l < 8; l++) {
                int res = screen[registers[y] * 64 + registers[x] + l + j * 64] ^ ((memory[i + j] >> (7 - l)) & 0b1);

                // Erase event
                if(screen[registers[y] * 64 + registers[x] + l + j * 64] == 1 && res == 0) registers[15] = 1;
                screen[registers[y] * 64 + registers[x] + l + j * 64] = res;
            }
        }
    }

    // 0xE type
    if(instructionType == 0xE) {
        if(y == 0x9 && instructionSubType == 0xE && keyboard[x] == 1) pc += 4;
        if(y == 0xA && instructionSubType == 0x1 && keyboard[x] == 0) pc += 4;
    }

    // 0xF type
    if(instructionType == 0xF) {
        if(y == 0x0 && instructionSubType == 0x7) registers[x] = gpTimer;
        if(y == 0x0 && instructionSubType == 0xA) {
            wait = 1;

            for(int j = 0; j < 16; j++) {
                if(keyboard[j] == 1) {
                    registers[x] = j;
                    wait = 0;
                    break;
                }
            }
        }
        if(y == 0x1 && instructionSubType == 0x5) gpTimer = registers[x];
        if(y == 0x1 && instructionSubType == 0x8) soundTimer = registers[x];
        if(y == 0x1 && instructionSubType == 0xE) i = i + registers[x];
        if(y == 0x2 && instructionSubType == 0x9) i = 0x6 * registers[x];
        if(y == 0x3 && instructionSubType == 0x3) {
            memory[i] = registers[x] / 100;
            memory[i + 1] = (registers[x] / 10) % 10;
            memory[i + 2] = registers[x] % 10;
        }
        if(y == 0x5 && instructionSubType == 0x5) {
            for(int j = 0; j < x + 1; j++) memory[i + j] = registers[j];
        }
        if(y == 0x6 && instructionSubType == 0x5) {
            for(int j = 0; j < x + 1; j++) registers[j] = memory[i + j];
        }
    }

    // Increment PC if nothing else already changed it
    if(pc == lastPC && wait == 0) pc += 2;
}