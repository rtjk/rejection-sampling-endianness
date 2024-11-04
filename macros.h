
// INCLUDES

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// FUNCTIONS

#define ROUND_UP(amount, round_amt) ( (((amount)+(round_amt)-1)/(round_amt))*(round_amt) )

#define IS_REPRESENTABLE_IN_D_BITS(D, N)                \
(((uint32_t) (N)>=(1UL << ((D)-1)) && (uint32_t) (N)<(1UL << (D))) ? (D) : -1)

#define BITS_TO_REPRESENT(N)                            \
  ((N) == 0 ? 1 : (15                                   \
                 + IS_REPRESENTABLE_IN_D_BITS( 1, N)    \
                 + IS_REPRESENTABLE_IN_D_BITS( 2, N)    \
                 + IS_REPRESENTABLE_IN_D_BITS( 3, N)    \
                 + IS_REPRESENTABLE_IN_D_BITS( 4, N)    \
                 + IS_REPRESENTABLE_IN_D_BITS( 5, N)    \
                 + IS_REPRESENTABLE_IN_D_BITS( 6, N)    \
                 + IS_REPRESENTABLE_IN_D_BITS( 7, N)    \
                 + IS_REPRESENTABLE_IN_D_BITS( 8, N)    \
                 + IS_REPRESENTABLE_IN_D_BITS( 9, N)    \
                 + IS_REPRESENTABLE_IN_D_BITS(10, N)    \
                 + IS_REPRESENTABLE_IN_D_BITS(11, N)    \
                 + IS_REPRESENTABLE_IN_D_BITS(12, N)    \
                 + IS_REPRESENTABLE_IN_D_BITS(13, N)    \
                 + IS_REPRESENTABLE_IN_D_BITS(14, N)    \
                 + IS_REPRESENTABLE_IN_D_BITS(15, N)    \
                 + IS_REPRESENTABLE_IN_D_BITS(16, N)    \
                 )                                      \
   )

// CONSTANTS

#define N 127
#define Q 127
#define BITS_N_ZQ_CT_RNG 923

#define BITS_FOR_Q BITS_TO_REPRESENT(Q-1)

#define CORRECTION_FQ_VEC ((BITS_N_ZQ_CT_RNG - N*BITS_FOR_Q)* (BITS_FOR_Q-1))
#define BUFSIZE_FQ_VEC (ROUND_UP(BITS_N_ZQ_CT_RNG+CORRECTION_FQ_VEC,8)/8)