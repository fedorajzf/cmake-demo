#include "../include/math-basic.h"

#include <assert.h>

int main(int argc, char **argv)
{
    MathBasic *mathLib = new MathBasic();
    assert (mathLib->multiply(2, 4) == 8);
    return 0;
}
