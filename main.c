
#include "prng.h"
#include "print.h"

int main() {

    uint8_t res[N];

    original_prng(res);

    print_sampled("res", res, N);

}
