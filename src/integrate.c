#include "integrate.h"

double simpson13(double (*f)(double x), double lower, double upper, uint32_t interval) {
    double h = (upper - lower) / interval;
    double sum = f(lower) + f(upper);
    for (uint32_t j = 1; j <= (uint32_t) (interval / 2) - 1; j++) {
        sum += 2.0 * f(lower + 2.0 * j * h);
    }
    for (uint32_t j = 1; j <= (uint32_t) (interval / 2); j++) {
        sum += 4.0 * f(lower + (2.0 * j - 1.0) * h);
    }

    sum *= h / 3.0;
    return sum;
}


