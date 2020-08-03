//
// Created by Oleg Kuzenko on 02.08.2020.
//

#ifndef I_SHUNTING_YARD_CALCULATOR_H
#define I_SHUNTING_YARD_CALCULATOR_H

#include "Node.h"

namespace shunting_yard {
    namespace calculator {
        // RPN list
        using RPN = std::vector<std::string>;

        class IShuntingYardCalculator {
        public:
            virtual ~IShuntingYardCalculator() = default;
        protected:

            virtual double evaluate(const std::shared_ptr<Node>& tree) = 0;
            virtual std::stack<std::shared_ptr<shunting_yard::calculator::Node>> parse(RPN rpn) = 0;
            virtual RPN reversePolishNotation(const std::string& eqn) = 0;
        };
    }
}

#endif //I_SHUNTING_YARD_CALCULATOR_H
