
#include "prng.h"
#include "print.h"
#include "endianness.h"

int main() {

    uint8_t res[N];

    original_prng(res);

    print_sampled("res", res, N);

    runtime_endianness_1();
    runtime_endianness_2();
    compiletime_endianness_1();
    compiletime_endianness_2();
    compiletime_endianness_3();
    compiletime_endianness_4();

}
