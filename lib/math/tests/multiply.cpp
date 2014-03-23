#include "../include/math.h"

#include <assert.h>

int main(int argc, char **argv)
{
    Math *mathLib = new Math();
    assert (mathLib->multiply(2, 4) == 8);
    return 0;
}
