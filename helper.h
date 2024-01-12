#include <stdio.h>
#include <string.h>

int min(int x, int y) {
    return (x <= y) ? x : y;
}

int min_of_three(int x, int y, int z) {
    return (x < y) ? min(x, z) : min(y, z);
}