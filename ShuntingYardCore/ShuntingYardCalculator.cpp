//
// Created by Oleg Kuzenko on 02.08.2020.
//

#include "ShuntingYardCalculator.h"
#include "Operations.h"

namespace {
    static const char _spaceCharacter = ' ';
    static const char _commaCharacter = ',';
    static const char _leftRoundBracketCharacter = '(';
    static const char _rightRoundBracketCharacter = ')';

    static const char _leftSquareBracketCharacter = '[';
    static const char _rightSquareBracketCharacter = ']';

    static const char _leftCurlyBracketCharacter = '{';
    static const char _rightCurlyBracketCharacter = '}';

    // Operators
    static const std::vector<char> operators = { shunting_yard::calculator::_plusOperator,
                                                 shunting_yard::calculator::_minusOperator,
                                                 shunting_yard::calculator::_divisionOperator,
                                                 shunting_yard::calculator::_multiplicationOperator,
                                                 shunting_yard::calculator::_squareOperator };

    // Left brackets
    static const std::vector<char> leftBrackets = { _leftRoundBracketCharacter, _leftCurlyBracketCharacter, _leftSquareBracketCharacter };

    // Right brackets
    static const std::vector<char> rightBrackets = { _rightRoundBracketCharacter, _rightCurlyBracketCharacter, _rightSquareBracketCharacter };
}

double shunting_yard::calculator::ShuntingYardCalculator::evaluateEquation(const std::string& equation) {
    if (equation.length() == 0) {
        throw std::runtime_error("Error: empty equation for evaluation.");
    }

    RPN rpn = reversePolishNotation(equation.c_str());
    auto tree = parse(rpn);
    return evaluate(tree.top());;
}

// Parse infix notation into reverse polish notation (Shunting Yard)
shunting_yard::calculator::RPN shunting_yard::calculator::ShuntingYardCalculator::reversePolishNotation(const std::string& eqn) {
    std::vector<std::string> queue;
    std::stack<std::string> stack;

    std::string obj;
    shunting_yard::calculator::TokenTypes type = shunting_yard::calculator::TokenTypes::ELSE;
    shunting_yard::calculator::TokenTypes prevType = shunting_yard::calculator::TokenTypes::ELSE; // Detecting negative signs

    // Reading and detecting tokens
    for (std::string::size_type index = 0; index < eqn.size(); ++index) {
        char t = eqn[index];

        // Skip spaces and commas
        if (t == _spaceCharacter || t == _commaCharacter) {
            prevType = shunting_yard::calculator::TokenTypes::ELSE;
            continue;
        }

        // Classify token based on the first character
        if (shunting_yard::utils::isNumber(t)) {
            type = shunting_yard::calculator::TokenTypes::CONSTANT;

            std::string::size_type startIndex = index;
            if (index < eqn.size() - 1) {
                while (shunting_yard::utils::isNumber(eqn[index + 1])) {
                    ++index;
                    if (index >= eqn.size() - 1) {
                        break;
                    }
                }
            }
            obj = eqn.substr(startIndex, index - startIndex + 1);

            // Subtraction sign detection
            if (obj == std::string(1, _minusOperator) && prevType != shunting_yard::calculator::TokenTypes::RPAREN && prevType != shunting_yard::calculator::TokenTypes::OPERATOR) {
                type = shunting_yard::calculator::TokenTypes::OPERATOR;
            }
        }
        else {
            auto functionName = shunting_yard::utils::findElement(index, eqn, shunting_yard::calculator::functionNames);
            if (functionName) {
                // Found valid function name object
                obj = *functionName;
                type = shunting_yard::utils::contains<char>(operators, obj[0]) ? shunting_yard::calculator::TokenTypes::OPERATOR : shunting_yard::calculator::TokenTypes::FUNCTION;
            }
            else {
                auto constantName = shunting_yard::utils::findElement(index, eqn, shunting_yard::calculator::constantNames);
                if (constantName) {
                    // Found valid object
                    obj = *constantName;
                    type = shunting_yard::calculator::TokenTypes::CONSTANT;
                }
                else {
                    if (shunting_yard::utils::contains<char>(leftBrackets, t)) {
                        type = shunting_yard::calculator::TokenTypes::LPAREN;
                        obj = _leftRoundBracketCharacter;
                    }
                    else if (shunting_yard::utils::contains<char>(rightBrackets, t)) {
                        type = shunting_yard::calculator::TokenTypes::RPAREN;
                        obj = _rightRoundBracketCharacter;
                    }
                    else {
                        type = shunting_yard::calculator::TokenTypes::ELSE;
                    }
                }
            }

            index += obj.size() - 1;
        }

        // Do something with the token
        const char* last_stack = (stack.size() > 0) ? stack.top().c_str() : ""; // Get last item on the stack
        switch (type) {
            case shunting_yard::calculator::TokenTypes::CONSTANT:
                queue.push_back(obj);
                break;
            case shunting_yard::calculator::TokenTypes::FUNCTION:
                stack.push(obj);
                break;
            case shunting_yard::calculator::TokenTypes::OPERATOR:
                if (stack.size() != 0) {
                    while (((shunting_yard::utils::contains<std::string>(shunting_yard::calculator::functionNames, last_stack) &&
                             !shunting_yard::utils::contains<char>(operators, last_stack[0])) ||
                            shunting_yard::utils::getPrecedence(last_stack) > shunting_yard::utils::getPrecedence(obj) ||
                            ((shunting_yard::utils::getPrecedence(last_stack) == shunting_yard::utils::getPrecedence(obj)) &&
                            shunting_yard::utils::isLeftAssociative(last_stack))) &&
                           !shunting_yard::utils::contains<char>(leftBrackets, last_stack[0])
                            ) {
                        queue.push_back(stack.top());
                        stack.pop();
                        if (stack.size() == 0) {
                            break;
                        }
                        last_stack = stack.top().c_str();
                    }
                }
                stack.push(obj);
                break;
            case shunting_yard::calculator::TokenTypes::LPAREN:
                stack.push(obj);
                break;
            case shunting_yard::calculator::TokenTypes::RPAREN:
                while (last_stack[0] != _leftRoundBracketCharacter) {
                    queue.push_back(stack.top());
                    stack.pop();
                    last_stack = stack.top().c_str();
                }
                stack.pop();
                break;
            default:
                return queue;
        }

        // Reset type
        prevType = type;
    }

    while (stack.size() > 0) {
        queue.push_back(stack.top());
        stack.pop();
    }

    return queue;
}

// Parse RPN to tree
std::stack<std::shared_ptr<shunting_yard::calculator::Node>> shunting_yard::calculator::ShuntingYardCalculator::parse(RPN rpn) {
    std::stack<std::shared_ptr<Node>> stack;

    for (std::string item : rpn) {
        if (shunting_yard::utils::isNumber(item.c_str())) {
            // Push number node
            stack.push(std::make_shared<NumNode>(item));
        }
        else {
            // Otherwise this is a function
            auto f = std::make_shared<FuncNode>(item);
            if (shunting_yard::utils::contains<std::string>(keys(shunting_yard::calculator::binary_functions), item)) {
                f->setUnary(false);

                // Set children of node
                f->setRightNode(stack.top());
                stack.pop();

                f->setLeftNode(stack.top());
                stack.pop();
            }
            else if (shunting_yard::utils::contains<std::string>(keys(shunting_yard::calculator::unary_functions), item)) {
                f->setUnary(true);

                // Set child node
                f->setLeftNode(stack.top());
                stack.pop();
            }
            stack.push(f);
        }
    }

    if (stack.size() == 0) {
        throw std::runtime_error("Error: stack is empty.");
    }

    return stack;
}

// Evaluate tree
double shunting_yard::calculator::ShuntingYardCalculator::evaluate(const std::shared_ptr<Node>& tree) {
    if (!tree) {
        throw std::runtime_error("Error: node element is empty.");
    }

    if (tree->isFunction()) {
        std::shared_ptr<FuncNode> fTree = std::dynamic_pointer_cast<FuncNode>(tree);
        if (!fTree) {
            throw std::runtime_error("Error: something wrong in the inheritance structure.");
        }

        if (fTree->isUnary) {
            return fTree->evaluate(evaluate(tree->getLeftNode()));
        }
        else {
            return fTree->evaluate(evaluate(tree->getLeftNode()), evaluate(tree->getRightNode()));
        }
    }
    else {
        // Number node
        return tree->evaluate();
    }
}
