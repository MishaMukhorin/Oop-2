//
// Created by Misha on 21.02.2024.
//
#include <gtest/gtest.h>
#include "../EvaluateExpr.h"
#include "../EvaluateExprErrors.h"

using namespace std;

TEST(EvaluateExprTest, ValidSingleOperand)
{
    EXPECT_EQ(EvaluateExpression("(* 8)"), 8);
}

TEST(EvaluateExprTest, ValidTwoOperands)
{
    EXPECT_EQ(EvaluateExpression("(+ 2 3)"), 5);
    EXPECT_EQ(EvaluateExpression("(* 2 4)"), 8);
}

TEST(EvaluateExprTest, ValidMultipleOperands)
{
    EXPECT_EQ(EvaluateExpression("(+ 2 3 4)"), 9);
    EXPECT_EQ(EvaluateExpression("(* 2 3 4)"), 24);
}

TEST(EvaluateExprTest, ValidNestedExpressions)
{
    EXPECT_EQ(EvaluateExpression("(+ 5 (* 2 3 2) (+ 5 (+ 2 5) (* 2 2)))"), 33);
}

TEST(EvaluateExprTest, ValidWithNegativeOperand)
{
    EXPECT_EQ(EvaluateExpression("(+ -2 3)"), 1);
}

TEST(EvaluateExprTest, ValidSinglOperand)
{
    EXPECT_EQ(EvaluateExpression("(* 8)"), 8);
}

TEST(EvaluateExprTest, ValidComplexExpression)
{
    EXPECT_EQ(EvaluateExpression("(+ (* 2 3) (* 3 4))"), 18);
    EXPECT_EQ(EvaluateExpression("(* (+ 1 2) (+ 3 1))"), 12);
    EXPECT_EQ(EvaluateExpression("(+ 5 (* 2 3 2) (+ 5 (+ 2 5) (* 2 2)))"), 33);
    EXPECT_EQ(EvaluateExpression("(+5(*2 3 2)(+5(+2 5)(*2 2)))"), 33);
    EXPECT_EQ(EvaluateExpression("(+ -2 3)"), 1);
}

TEST(EvaluateExprTest, InvalidExpressions)
{
    EXPECT_THROW(EvaluateExpression("(+ 5 (* 2 3 2) (+ 5 (+ 2 5) (* 2))"), NoClosingParenthesesError);
    EXPECT_THROW(EvaluateExpression("( 2 3 2)"), NoOperatorError);
    EXPECT_THROW(EvaluateExpression("(+ )"), NoOperandsInParenthesesError);
    EXPECT_THROW(EvaluateExpression("2( + )"), NumberOutsideTheParenthesesError);
    EXPECT_THROW(EvaluateExpression("+ )"), NoOpeningParenthesisError);
    EXPECT_THROW(EvaluateExpression("&&+ )"), InvalidCharacterError);
    EXPECT_THROW(EvaluateExpression("(+ -)"), NoNumberAfterMinusError);
    EXPECT_THROW(EvaluateExpression("((+ 2 -)"), NoOperatorError);
}

TEST(EvaluateExprTest, OutOfBoundsIntegers)
{
    EXPECT_EQ(EvaluateExpression("(+9223372036854775807)"), INT64_MAX);
    EXPECT_THROW(EvaluateExpression("(+9223372036854775808)"), TooLargeNumberError);
    EXPECT_EQ(EvaluateExpression("(+ -9223372036854775807)"), -INT64_MAX);
    EXPECT_THROW(EvaluateExpression("(+ -9223372036854775808)"), TooLargeNumberError); //todo intmin
}



GTEST_API_ int main(int argc, char **argv)
{
    cout << "Running tests \n";
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

