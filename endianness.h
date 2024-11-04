
#include "macros.h"

void runtime_endinness() {
    uint16_t num = 0x1;
    printf("\nruntime_endinness: ");
    (*(uint8_t *)&num == 0) ? printf("BIG\n") : printf("LITTLE\n");
}