
#include "macros.h"

void simple_randombytes(unsigned char *x, unsigned long long xlen) {
    for (unsigned long long i = 0; i < xlen; i++) {
        x[i] = (unsigned char) (rand() % 256);
    }
}

static inline void original_prng(uint8_t res[N]){

    const uint8_t mask = ( (uint8_t) 1 << BITS_FOR_Q) - 1;
    
    uint8_t CSPRNG_buffer[BUFSIZE_FQ_VEC];

    simple_randombytes(CSPRNG_buffer, BUFSIZE_FQ_VEC);

    int placed = 0;
    uint64_t sub_buffer = *(uint64_t *)CSPRNG_buffer;
    int bits_in_sub_buf = 64;

    int pos_in_buf = 8;

    while (placed < N) {
        if (bits_in_sub_buf <= 32) {
            uint32_t refresh_buf = *(uint32_t *) (CSPRNG_buffer + pos_in_buf);
            pos_in_buf += 4;
            sub_buffer |=  ((uint64_t) refresh_buf) << bits_in_sub_buf;
            bits_in_sub_buf += 32;
        }
        res[placed] = sub_buffer & mask;
        if (res[placed] < Q) {
            placed++;
            sub_buffer = sub_buffer >> BITS_FOR_Q;
            bits_in_sub_buf -= BITS_FOR_Q;

        } else {
            sub_buffer = sub_buffer >> 1;
            bits_in_sub_buf -= 1;
        }
    }
}

