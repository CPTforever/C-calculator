#pragma once

#include <inttypes.h>

double simpson13(double (*f)(double x), double lower, double upper, uint32_t interval);
