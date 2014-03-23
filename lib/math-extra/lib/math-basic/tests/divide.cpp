#include "../include/math-basic.h"

#include <assert.h>

int main(int argc, char **argv)
{
    MathBasic *mathLib = new MathBasic();
    assert (mathLib->divide(8, 2) == 4);
    return 0;
}
