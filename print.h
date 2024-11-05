
#include "macros.h"

static void print_array(const char *name, unsigned char *array, unsigned long long len) {
    printf("%s: ", name);
    for (size_t i = 0; i < len; i++) {
        if(i < 3) printf("%02x", array[i]);
        else if(i == len/2) printf(" ... ");
        else if(i > (len-4)) printf("%02x", array[i]);
    }
    printf("\n");
}

static void print_array_full(const char *name, unsigned char *array, unsigned long long len) {
    printf("%s: ", name);
    for (size_t i = 0; i < len; i++) {
        printf("%02x", array[i]);
    }
    printf("\n");
}

static void print_sampled(const char *name, uint8_t *array, unsigned long long len) {
    printf("%s: ", name);
    for (size_t i = 0; i < len; i++) {
        printf("%d,", array[i]);
    }
    printf("\n");
}

void print_bits(uint8_t num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

void print_bytes(uint16_t num) {
    uint8_t *byte_ptr = (uint8_t*)&num;
    for (int i = 0; i < 2; i++) {
        print_bits(byte_ptr[i]);
        printf(" ");
    }
    printf("\n");
}