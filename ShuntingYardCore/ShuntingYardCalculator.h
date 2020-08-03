//
// Created by Oleg Kuzenko on 02.08.2020.
//

#ifndef SHUNTINGYARD_SHUNTINGYARDCALCULATOR_H
#define SHUNTINGYARD_SHUNTINGYARDCALCULATOR_H

#include <cstring>
#include <algorithm>
#include <stack>
#include <string>

#include "IShuntingYardCalculator.h"
#include "ShuntingYardUtils.h"

namespace shunting_yard
{
    namespace calculator {

        class ShuntingYardCalculator: public IShuntingYardCalculator {
            double evaluate(const std::shared_ptr<Node>& tree) override;
            std::stack<std::shared_ptr<shunting_yard::calculator::Node>> parse(shunting_yard::calculator::RPN rpn) override;
            RPN reversePolishNotation(const std::string& eqn) override;

        public:
            double evaluateEquation(const std::string& equation);
        };
    }
}

#endif //SHUNTINGYARD_SHUNTINGYARDCALCULATOR_H
