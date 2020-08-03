//
// Created by Oleg Kuzenko on 02.08.2020.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ShuntingYardCalculator.h"

// TODO: add mockable methods

TEST(ShuntingYardCalculatorUnitTest, expectExceptionOnEmptyEquationString) {
    auto calculator = std::make_unique<shunting_yard::calculator::ShuntingYardCalculator>();
    EXPECT_ANY_THROW(calculator->evaluateEquation(""));
}
