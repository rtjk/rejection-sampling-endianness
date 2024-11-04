
#include "prng.h"
#include "print.h"
#include "endianness.h"

int main() {

    uint8_t res[N];

    original_prng(res);

    print_sampled("res", res, N);

    runtime_endinness_1();
    runtime_endinness_2();
    compiletime_endinness_1();
    compiletime_endinness_2();

}
