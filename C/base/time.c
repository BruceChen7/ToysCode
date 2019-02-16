#include "base/time.h"
#include <sys/time.h>
#include <stdlib.h>

long long timeInMilliseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
