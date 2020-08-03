#include <iostream>

#include "ShuntingYardCalculator.h"

using std::endl;
using std::cout;

// sin(3^-2 * 27 / 4 * pi) + 1

int main()
{
    std::cout << "Input equation: ";
    std::string eqn = "sin(3^-2 * 27 / 4 * pi) + 1";
//    std::getline(std::cin, eqn);

    auto calculator = std::make_unique<shunting_yard::calculator::ShuntingYardCalculator>();
    std::cout << " = " << calculator->evaluateEquation(eqn) << std::endl;

    return 0;
}
