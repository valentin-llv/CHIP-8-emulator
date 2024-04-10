#include <stdlib.h>

int randimInt(int min, int max) {
    return rand() % (max + 1 - min) + min;
}