// # pragma once
#include <stdio.h>

union Data
{
    int num;   // 4 bytes
    char byte; // 1 byte (overlaps with the lowest byte of 'num' on x86_64)
};

typedef struct
{
    int x;
    int y;
    int z;
} Point;

int main(void)
{
    union Data d;
    Point p1 = {10, 20, 30};      // use Point directly without "struct" keyword
    Point p2 = {.x = 5, .y = 15}; // "designated initializer" (C99+) for clarity - also if you have an empty field in this case z it gets filled with a 0 - also with 10, 20, 30 above you have to remember what 10 20 30 are assigning to x y and z  listing it here makes it clearer

    // Both pointers print the EXACT same memory address
    printf("\n");
    printf("Address of d.num: %p\n", (void *)&d.num);
    printf("Address of d.byte %p\n", (void *)&d.byte);
    printf("\n");

    // Addresses of struct are different for the fields
    printf("p1 addresses: \n\tp1.x: %p\n\tp1.y: %p\n\tp1.z: %p\n", (void *)&p1.x, (void *)&p1.y, (void *)&p1.z);

    printf("p1 fields: \n\tp1.x: %d\n\tp1.y: %d\n\tp1.z: %d\n", p1.x, p1.y, p1.z);
    printf("p2 fields: \n\tp2.x: %d\n\tp2.y: %d\n\tp2.z: %d\n", p2.x, p2.y, p2.z);
}

// Format specifiers in C are placeholders used in format strings to specifiy the type and format of the line/output.
// %p format specificer: used for displaying pointers in a human-readable format. Something like "0x7ffee706736c"
// reminder: gcc -o [name_of_executable_arbitrary] [file.c] - makes the executable
// ./name_of_executable_arbitrary - runs the code
// gcc -o union union.c && ./union

/* struct Point {
    int x;
    int y;
    int z;
};  writing like this requires us to wrie struct on each initialization */

// initialization is the word for assigning values at the exact moment a variable is created

// int is 4 bytes (32 bitss) on almost all modern 64-bit systems (Linux, macOS, and Windows)
// pointers (int*, void*, etc.) are 8 bytes on 64-bit systems along with long long
// sizeof is a built-in operator (not a function).

// & "address-of" operator: in front of any variable in C asks "What is the exact memory address where this variable lives?"