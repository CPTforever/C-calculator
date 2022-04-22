#include "mathlib.h"

#include <stdio.h>
#define PI    3.1415926535897932384
#define EULER 2.7182818284590452353

// PURPOSE:
// This takes the modulo of a double
//
// INPUT:
// double x: The left hand operand
// double o: The right hand operand
//
// OUTPUT:
// Returns the output of the modulo
//
double modulus(double x, double o) {
    while (Abs(x) > o) {
        x += x > 0 ? -1 * o : o;
    }
    return x;
}

// PURPOSE:
// Returns the e^x given x using Taylor series
//
// INPUT:
// double x: The input of the function
// The value explodes because of the nature of exponentials
// e^100 has 43 digits so keep the values small
//
// OUTPUT:
// Returns e^x and inverts if if x was negative
// because that would be computationally faster
//
// ATTRIBUTIONS;
// The pseudo-code was observed when making this function
//
double Exp(double x) {
    double trm = 1.0, sum = 1.0, k = 1.0;
    while (trm > EPSILON) {
        trm *= Abs(x) / k;
        sum += trm;
        k += 1;
    }
    return x > 0 ? sum : 1 / sum;
}

// PURPOSE:
// Returns the sin(x) given x using Taylor series
//
// INPUT:
// double x: The input of the function
//
// OUTPUT:
// First modulo the input by 2PI to prevent overflow and save time
// Then use the Taylor series to approximate the normalized value
//
// ATTRIBUTIONS;
// The pseudo-code was used when making this function
//
double Sin(double x) {
    x = modulus(x, 2 * PI);
    double s = 1.0, k = 3.0;
    double v = x, t = x;
    while (Abs(t) > EPSILON) {
        t *= (x * x) / ((k - 1) * k);
        s = -s;
        v += s * t;
        k += 2.0;
    }
    return v;
}

// PURPOSE:
// Returns the cos(x) given x using Taylor series
//
// INPUT:
// double x: The input of the function
//
// OUTPUT:
// First modulo the input by 2PI to prevent overflow and save time
// Then use the Taylor series to approximate the normalized value
//
// ATTRIBUTIONS;
// The pseudo-code was used when making this function
//
double Cos(double x) {
    x = modulus(x, 2 * PI);
    double s = 1.0, v = 1.0, k = 1.0, t = 1.0;
    while (Abs(t) > EPSILON) {
        t = t * (x * x) / ((k + 1) * k);
        s = -s;
        v += s * t;
        k += 2.0;
    }
    return v;
}

// PURPOSE:
// Returns the sqrt(x) given x using Newton Approximation
//
// INPUT:
// double x: The input of the function
// It is assumed x isn't negative
//
// OUTPUT:
// First factor out multiples of 4
// Then use Newton Approximation to calculate the normalized value
//
// ATTRIBUTIONS;
// The pseudo-code was used when making this function
//
double Sqrt(double x) {

    double z = 0.0, y = 1.0;

    double f = 1.0;
    while (x > 1) {
        x /= 4.0;
        f *= 2.0;
    }
    while (Abs(y - z) > EPSILON) {
        z = y;
        y = 0.5 * (z + x / z);
    }
    return f * y;
}

// PURPOSE:
// Returns the log(x) given x using Newton Approximation
//
// INPUT:
// double x: The input of the function
// It is assumed x isn't negative
//
// OUTPUT:
// First factor out multiples of Euler's constant
// Then use Newton Approximation to calculate the normalized value
//
// ATTRIBUTIONS;
// The pseudo-code was used when making this function
//
double Log(double x) {
    double y = 1.0, f = 0.0;
    double p = Exp(y);

    while (x > EULER) {
        f += 1.0;
        x /= EULER;
    }

    while (Abs(p - x) > EPSILON) {
        y = y + x / p - 1;
        p = Exp(y);
    }

    return f + y;
}
