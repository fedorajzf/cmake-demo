#include "../include/math-extra.h"

#include "math-basic.h"

int MathExtra::power(int base, int exponent)
{
    if (exponent == 0) {
        return 1;
    }

    int result = 1;
    MathBasic *mathLib = new MathBasic();
    for (int i = 0; i < exponent; i++) {
        result = mathLib->multiply(result, base);
    }

    return result;
}
