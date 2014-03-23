#include "../include/math-extra.h"

#include <assert.h>

int main(int argc, char **argv)
{
    MathExtra *mathExtraLib = new MathExtra();
    assert(mathExtraLib->power(3, 3) == 27);
    return 0;
}
