//
// Created by Oleg Kuzenko on 02.08.2020.
//

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <map>
#include <cmath>
#include <map>
#include <iterator>
#include <algorithm>
#include <vector>

namespace shunting_yard {
    namespace calculator {

        enum class TokenTypes {
            OPERATOR,
            CONSTANT,
            FUNCTION,
            LPAREN,
            RPAREN,
            ELSE
        };

        static const char _plusOperator = '+';
        static const char _minusOperator = '-';
        static const char _divisionOperator = '/';
        static const char _multiplicationOperator = '*';
        static const char _squareOperator = '^';

        // Callback to unary function (1 argument)
        typedef double(*UnaryFuncEval)(double x);

        // Callback to binary function (2 arguments)
        typedef double(*BinaryFuncEval)(double x, double y);

        class Func {
        public:
            Func() : m_type(TokenTypes::OPERATOR), m_prec(0), m_left(true), m_unary(true), m_uEval(nullptr), m_bEval(nullptr) {}

            // Constructor for unary functions
            Func(UnaryFuncEval eval, TokenTypes type = TokenTypes::FUNCTION, uint16_t prec = 0, bool left = true)
                    : Func(type, prec, left, true) {
                m_uEval = eval;
            }

            // Contructor for binary functions
            Func(BinaryFuncEval eval, TokenTypes type = TokenTypes::FUNCTION, uint16_t prec = 0, bool left = true)
                    : Func(type, prec, left, false) {
                m_bEval = eval;
            }

            double eval(double x, double y = 0) {
                return this->m_unary ? m_uEval(x) : m_bEval(x, y);
            }

            bool isLeftAssiciative() const { return m_left; }
            uint16_t getPrecedence() const { return m_prec; }

        private:
            Func(TokenTypes type, uint16_t prec, bool left, bool unary)
                    : m_type(type), m_prec(prec), m_left(left), m_unary(unary), m_uEval(nullptr), m_bEval(nullptr) {}

        private:
            UnaryFuncEval m_uEval;
            BinaryFuncEval m_bEval;

            TokenTypes m_type; // Type of function (ie function or operator)
            uint16_t m_prec; // Precedence
            bool m_left; // Is left associative
            bool m_unary; // Is a unary function
        };

        // Unary functions
        static std::map<std::string, shunting_yard::calculator::Func> unary_functions = {
                { "sin", shunting_yard::calculator::Func(std::sin) }
        };

        // Obtain key list
        template<typename T>
        std::vector<std::string> keys(std::map<std::string, T> m) {
            std::vector<std::string> keys;
            keys.reserve(m.size());

            std::transform(m.begin(), m.end(), std::back_inserter(keys),
                    [](const auto& pair){ return pair.first; });

            return keys;
        }

        // Obtain combined key list
        template<typename T>
        std::vector<std::string> keys(std::map<std::string, T> m1, std::map<std::string, T> m2) {
            // Get keys from each map
            std::vector<std::string> keySet1 = keys<T>(m1);
            std::vector<std::string> keySet2 = keys<T>(m2);

            // Insert the second list into first
            std::copy(keySet2.begin(), keySet2.end(), std::back_inserter(keySet1));

            return keySet1;
        }

        static std::map<std::string, double> constants = {
                {"pi", std::atan(1) * 4 },
                {"e", std::exp(1) }
        };

        static std::vector<std::string> constantNames = keys<double>(constants);

        // Binary functions
        static std::map<std::string, shunting_yard::calculator::Func> binary_functions = {
                { std::string(1, _plusOperator), shunting_yard::calculator::Func([](double x, double y) -> double {return x + y; }, shunting_yard::calculator::TokenTypes::OPERATOR, 2) },
                { std::string(1, _minusOperator), shunting_yard::calculator::Func([](double x, double y) -> double {return x - y; }, shunting_yard::calculator::TokenTypes::OPERATOR, 2) },
                { std::string(1, _multiplicationOperator), shunting_yard::calculator::Func([](double x, double y) -> double {return x * y; }, shunting_yard::calculator::TokenTypes::OPERATOR, 3) },
                { std::string(1, _divisionOperator), shunting_yard::calculator::Func([](double x, double y) -> double {return x / y; }, shunting_yard::calculator::TokenTypes::OPERATOR, 3) },
                { std::string(1, _squareOperator), shunting_yard::calculator::Func(std::pow, shunting_yard::calculator::TokenTypes::OPERATOR, 4, false) }
        };

        // Function names
        static std::vector<std::string> functionNames = keys<shunting_yard::calculator::Func>(unary_functions, binary_functions);
    }
}

#endif OPERATIONS_H
