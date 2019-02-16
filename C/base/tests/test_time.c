#include "base/time.h"
#include <stdint.h>

int main() {
    long long now = timeInMilliseconds();
    printf("now = %lld in milliseconds\n", now);
    long long start, elapsed;
    long long count = 10000000;
    startBenchMark();
    for (uint32_t i = 0; i < count; ++i) {

    }
    endBenchMark("for loop benchmark");

    return 0;
}
