/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 3: Alternative Concept - Byte-per-Device Array (char state[8])
 * Standard: C11
 */

#include <stdio.h>

enum { LIGHT = 0, FAN = 1, AC = 2, HEATER = 3, PUMP = 4 };

void array_switch_on(char state[8], int dev) {
    if (dev >= 0 && dev < 8) state[dev] = 1;
}

void array_switch_off(char state[8], int dev) {
    if (dev >= 0 && dev < 8) state[dev] = 0;
}

void array_toggle(char state[8], int dev) {
    if (dev >= 0 && dev < 8) state[dev] = (char)(!state[dev]);
}

int array_is_on(const char state[8], int dev) {
    if (dev >= 0 && dev < 8) return state[dev] ? 1 : 0;
    return 0;
}

int array_count_on(const char state[8]) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        count += state[i] ? 1 : 0;
    }
    return count;
}

void array_show(const char state[8]) {
    for (int bit = 7; bit >= 0; bit--) {
        putchar(state[bit] ? '1' : '0');
    }
    putchar('\n');
}

int main(void) {
    char state[8] = {0};

    array_switch_on(state, LIGHT);
    array_switch_on(state, AC);
    array_show(state);

    array_toggle(state, FAN);
    array_switch_off(state, LIGHT);
    array_show(state);

    printf("AC is %s, PUMP is %s\n",
           array_is_on(state, AC) ? "ON" : "OFF",
           array_is_on(state, PUMP) ? "ON" : "OFF");
    printf("Active devices count: %d\n", array_count_on(state));
    printf("Memory per home: Bitwise = %zu byte vs Array = %zu bytes\n",
           sizeof(unsigned char), sizeof(state));
    printf("Memory for 1,000,000 homes: Bitwise = 1,000,000 bytes (~0.95 MB) vs Array = 8,000,000 bytes (~7.63 MB)\n");

    return 0;
}
