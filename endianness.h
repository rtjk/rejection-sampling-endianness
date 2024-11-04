
#include "macros.h"

void runtime_endinness() {
    uint16_t num = 0x1;
    printf("runtime_endinness: ");
    (*(uint8_t *)&num == 0) ? printf("BIG\n") : printf("LITTLE\n");
}

void compiletime_endinness_1() {
    printf("compiletime_endinness_1: ");
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        printf("LITTLE\n");
    #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        printf("BIG\n");
    #else
        printf("UNKNOWN\n");
    #endif
}

void compiletime_endinness_2() {
    printf("compiletime_endinness_2: ");
    #ifdef __BIG_ENDIAN__
        printf("BIGGGGGGG\n");
    #endif

    #if defined(__LITTLE_ENDIAN__)
        printf("LITTLE\n");
    #elif defined(__BIG_ENDIAN__)
        printf("BIG\n");
    #else
        printf("UNKNOWN\n");
    #endif
}