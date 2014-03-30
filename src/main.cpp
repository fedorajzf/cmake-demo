#include "math-extra.h"
#include "math-basic.h"

#include <iostream>

int main(int argc, char **argv)
{
    MathExtra *mathExtraLib = new MathExtra();
    std::cout << "4 * 2 = " << mathExtraLib->multiply(4, 2) << "\n";
    std::cout << "4 / 2 = " << mathExtraLib->divide(4, 2) << "\n";
    std::cout << "4 ^ 2 = " << mathExtraLib->power(4, 2) << "\n";

    MathBasic *mathBasicLib = new MathBasic();
    std::cout << "4 * 2 = " << mathBasicLib->multiply(4, 2) << "\n";
    std::cout << "4 / 2 = " << mathBasicLib->divide(4, 2) << "\n";
    return 0;
}
