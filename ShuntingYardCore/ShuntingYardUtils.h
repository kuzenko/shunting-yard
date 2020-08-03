//
// Created by Oleg Kuzenko on 02.08.2020.
//

#ifndef SHUNTINGYARDUTILS_H
#define SHUNTINGYARDUTILS_H

#include <vector>
#include <string>

#include "Operations.h"

namespace shunting_yard
{
    namespace utils {
        // Determine if vector contains values
        template<typename T>
        bool contains(std::vector<T> v, T x) {
            return std::find(v.begin(), v.end(), x) != v.end();
        }

        // Determine if character is number
        static bool isNumber(char c) {
            return c == '.' || (int(c) >= int('0') && int(c) <= int('9')) || c == '-';
        }

        // Determine if string only contains numerical characters
        static bool containsNumbers(const char* str) {
            // Try to prove wrong
            for (char c : std::string(str)) {
                if (!isNumber(c)) {
                    return false;
                }
            }

            return true;
        }

        // Determine if entire string is a number
        static bool isNumber(const char* str) {
            return contains<std::string>(shunting_yard::calculator::constantNames, str) || std::strcmp(str, ".") == 0 || containsNumbers(str);
        }

        // Get numerical value of string
        static double getNumericalVal(const char* str) {
            if (contains<std::string>(shunting_yard::calculator::constantNames, str)) {
                return shunting_yard::calculator::constants[str];
            }

            return std::atof(str);
        }

        // Determine if string matches a function key
        static bool isFunction(std::string str) {
            return contains<std::string>(shunting_yard::calculator::functionNames, str);
        }

        // Determine if function is left associative
        static bool isLeftAssociative(std::string str) {
            // We are only doing for binary functions is because all the unary functions are left associative
            return shunting_yard::calculator::binary_functions[str].isLeftAssiciative();
        }

        // Get function precedence
        static short getPrecedence(std::string str) {
            // This is a function that only applies for binary functions
            // because the precedence of all the unary functions is all 0
            // because those are just pure functions
            if (contains<std::string>(keys(shunting_yard::calculator::binary_functions), str)) {
                return shunting_yard::calculator::binary_functions[str].getPrecedence();
            }

            return 0;
        }

        // Find element from list in the equation starting at index i
        static std::optional<std::string> findElement(uint32_t index, const std::string& eqn, const std::vector<std::string>& elements) {
            auto iter = find_if(elements.begin(), elements.end(), [&eqn, &index](const auto& element) {
                size_t size = element.size();
                if (eqn.substr(index, size) == element)
                    return true;

                return false;
            });

            if (iter != elements.end())
                return *iter;

            return {};
        }
    }
}

#endif //SHUNTINGYARDUTILS_H
