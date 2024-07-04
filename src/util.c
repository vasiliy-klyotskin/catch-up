#include <util.h>
#include <stdlib.h>

double min(const double a, const double b) {
    return (a < b) ? a : b;
}

double rand_minus1_1(void) {
    double normalized_0_1 = (double)rand() / RAND_MAX;
    double normalized_minus1_1 = 2 * normalized_0_1 - 1;
    return normalized_minus1_1;
}