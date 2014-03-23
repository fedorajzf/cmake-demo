#include "../include/math.h"

#include <assert.h>

int main(int argc, char **argv)
{
    Math *mathLib = new Math();
    assert (mathLib->divide(8, 2) == 4);
    return 0;
}
