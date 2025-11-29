#include "integral.h"
#include <math.h>

float sin_integral(float a, float b, float e) {
    float integral = 0.0f;
    for (float x = a; x < b; x += e) {
        integral += sinf(x) * e;
    }
    return integral;
}