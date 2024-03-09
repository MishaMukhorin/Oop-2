//
// Created by Misha on 21.02.2024.
//

#ifndef OOP_2_EVALUATEEXPR_H
#define OOP_2_EVALUATEEXPR_H

#include "string"
#include <stack>
#include <iostream>
#include <climits>

// todo перенести в cpp
enum class TokenType {
    Space,
    CloseParenthesis,
    Minus,
    Plus,
    Star,
    Digit,
};

//todo rename subExpr
struct Layer {
    char op{};
    long long result{};
    bool isNegative = false;//todo разделить ответственность
    bool changed = false;

    Layer(char operation, long long res, bool isNegative, bool changd) : op(operation), result(res), isNegative(isNegative), changed(changd) {}

};

long long EvaluateExpression(const std::string& expr);



#endif //OOP_2_EVALUATEEXPR_H
