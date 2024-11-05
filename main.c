
#include "prng.h"
#include "print.h"
#include "endianness.h"

int main() {

    uint8_t res[N];

    // original_prng(res);
    endian_prng(res);

    print_sampled("res", res, N);

}
