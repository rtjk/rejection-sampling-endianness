
#include "macros.h"

void simple_randombytes(unsigned char *x, unsigned long long xlen) {
    for (unsigned long long i = 0; i < xlen; i++) {
        x[i] = (unsigned char) (rand() % 256);
    }
}

//////////////////////////////////////////////////////////////////////////
/////////////////////////// ORIGINAL PRNG ////////////////////////////////
//////////////////////////////////////////////////////////////////////////

static inline void original_prng(uint8_t res[N]) {

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
            sub_buffer |= ((uint64_t) refresh_buf) << bits_in_sub_buf;
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

//////////////////////////////////////////////////////////////////////////
/////////////////////// ENDIANNESS-AWARE PRNG ////////////////////////////
//////////////////////////////////////////////////////////////////////////

#define BIG_ENDIAN_SYSTEM 0 // assume little-endian by default

/* check if we are on a big-endian system:
 * the __BYTE_ORDER__ macro is defined by the compiler
 * recent versions of GCC and Clang define it
 * other methods to detect endianness might be needed when using different compilers
 * (see file endianness.h) */
#if defined(__BYTE_ORDER__)&&(__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
    #undef BIG_ENDIAN_SYSTEM
    #define BIG_ENDIAN_SYSTEM 1
#endif

static inline uint64_t to_little_endian64(uint64_t x) {
    /* when compiling on a big-endian system, swap the bytes */
    #if BIG_ENDIAN_SYSTEM
        return __builtin_bswap64(x);
    #else
        return x;
    #endif
}

static inline uint32_t to_little_endian32(uint32_t x) {
    /* when compiling on a big-endian system, swap the bytes */
    #if BIG_ENDIAN_SYSTEM
        return __builtin_bswap32(x);
    #else
        return x;
    #endif
}

static inline void endian_prng(uint8_t res[N]) {

    const uint8_t mask = ( (uint8_t) 1 << BITS_FOR_Q) - 1;

    uint8_t CSPRNG_buffer[BUFSIZE_FQ_VEC];

    simple_randombytes(CSPRNG_buffer, BUFSIZE_FQ_VEC);

    int placed = 0;

    uint64_t sub_buffer = to_little_endian64(*(uint64_t *)CSPRNG_buffer);
    int bits_in_sub_buf = 64;
    int pos_in_buf = 8;

    while (placed < N) {
        if (bits_in_sub_buf <= 32) {
            uint32_t refresh_buf = to_little_endian32(*(uint32_t *) (CSPRNG_buffer + pos_in_buf));
            pos_in_buf += 4;
            sub_buffer |= ((uint64_t) refresh_buf) << bits_in_sub_buf;
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
