// # pragma once
#include <stdio.h>

union Data
{
    int num;   // 4 bytes
    char byte; // 1 byte (overlaps with the lowest byte of 'num' on x86_64)
};

/* struct Point {
    int x;
    int y;
    int z;
};  writing like this requires us to wrie struct on each initialization */

int main(void)
{
    union Data d;

    // Both pointers print the EXACT same memory address
    printf("Address of d.num: %p\n", (void *)&d.num);
    printf("Address of d.byte %p\n", (void *)&d.byte);
}

// Format specifiers in C are placeholders used in format strings to specifiy the type and format of the line/output.
// %p format specificer: used for displaying pointers in a human-readable format. Something like "0x7ffee706736c"
// reminder: gcc -o [name_of_executable_arbitrary] [file.c] - makes the executable
// ./name_of_executable_arbitrary - runs the code
// gcc -o union union.c && ./union