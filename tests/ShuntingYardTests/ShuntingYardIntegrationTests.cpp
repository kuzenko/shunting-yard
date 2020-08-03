//
// Created by Oleg Kuzenko on 02.08.2020.
//

#include <gtest/gtest.h>

#include "ShuntingYardCalculator.h"

class ShuntingYardIntegrationTest : public ::testing::Test
{
protected:
    std::unique_ptr<shunting_yard::calculator::ShuntingYardCalculator> calculator;

    virtual void SetUp()
    {
        calculator = std::make_unique<shunting_yard::calculator::ShuntingYardCalculator>();
    }

    virtual void TearDown()
    {
    }
};

TEST_F(ShuntingYardIntegrationTest, correctReturnValueForEquation1) {
    const std::string eqn = "sin(3^-2 * 27 / 4 * pi) + 1";
    EXPECT_NEAR(calculator->evaluateEquation(eqn), 1.70711, 0.001);
}

// TODO: add more equations
