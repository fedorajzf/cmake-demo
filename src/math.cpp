/*
 * math.cpp - Math function
 *
 * Copyright (C) 2014-2015 Takar.
 *
 * Written by Tamar Kranenburg <info@takar.nl>
 */

#include <iostream>

#include "math-extra.h"
#include "math-basic.h"

void math_extra() {
    MathExtra *mathExtraLib = new MathExtra();
    std::cout << "4 * 2 = " << mathExtraLib->multiply(4, 2) << "\n";
    std::cout << "4 / 2 = " << mathExtraLib->divide(4, 2) << "\n";
    std::cout << "4 ^ 2 = " << mathExtraLib->power(4, 2) << "\n";
}

void math_basic() {
    MathBasic *mathBasicLib = new MathBasic();
    std::cout << "4 * 2 = " << mathBasicLib->multiply(4, 2) << "\n";
    std::cout << "4 / 2 = " << mathBasicLib->divide(4, 2) << "\n";
}
