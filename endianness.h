
#include "macros.h"

// RUNTIME

void runtime_endianness_1() {
    printf("runtime_endianness: ");
    uint16_t num = 0x1;
    (*(uint8_t *)&num == 0) ? printf("BIG\n") : printf("LITTLE\n");
}

// https://stackoverflow.com/questions/8978935/detecting-endianness
void runtime_endianness_2() {
    printf("runtime_endianness: ");
    const union { unsigned u; unsigned char c[4]; } one = { 1 };   /* don't use static : performance detrimental  */
    (one.c[0] == 0) ? printf("BIG\n") : printf("LITTLE\n");
}

// COMPILE TIME

void print_endianness(int endianness) {
    printf("compiletime_endianness: ");
    if (endianness == 1) printf("LITTLE\n");
    if (endianness == -1) printf("BIG\n");
    if ((endianness != 1) && (endianness != -1)) printf("UNKNOWN\n");
}

void compiletime_endianness_1() {
    int endianness = 0;
    #if defined(__BYTE_ORDER__)&&(__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
        endianness++;
    #endif
    #if defined(__BYTE_ORDER__)&&(__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
        endianness--;
    #endif
    print_endianness(endianness);
    }

void compiletime_endianness_2() {
    int endianness = 0;
    #if defined(__LITTLE_ENDIAN__)
        endianness++;
    #endif
    #if defined(__BIG_ENDIAN__)
        endianness--;
    #endif
    print_endianness(endianness);
}

void compiletime_endianness_3() {
    int endianness = 0;
    #if defined(__LITTLE_ENDIAN)
        endianness++;
    #endif
    #if defined(__BIG_ENDIAN)
        endianness--;
    #endif
    print_endianness(endianness);
}

void compiletime_endianness_4() {
    int endianness = 0;
    #if defined(_LITTLE_ENDIAN)
        endianness++;
    #endif
    #if defined(_BIG_ENDIAN)
        endianness--;
    #endif
    print_endianness(endianness);
}