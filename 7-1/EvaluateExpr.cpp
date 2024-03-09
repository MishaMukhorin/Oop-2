//
// Created by Misha on 21.02.2024.
//

#include "EvaluateExpr.h"
#include "EvaluateExprErrors.h"

using namespace std;

//todo автоматизировать стиль написания кода

long long CheckNegative(bool& isNegative, long long num)
{
    num = isNegative ? -1 * num : num;
    isNegative = false;
    return num;
}

void ExecuteAnOperation(Layer& layer, long long currNum)
{
    if (layer.op == '*')
    {
        layer.result *= CheckNegative(layer.isNegative, currNum);
        layer.changed = true;
    }
    else
    {
        layer.result += CheckNegative(layer.isNegative, currNum);
        layer.changed = true;
    }
}

// todo rename i to pos
bool PopStack(stack<Layer> &st, long long& result, int i) {
    if (!st.empty())
    {
        Layer p = st.top();
        st.pop();
        if (!st.empty())
        {
            ExecuteAnOperation(st.top(), p.result);
            return false;
        }
        else
        {
            if (p.isNegative)
            {
                throw NoNumberAfterMinusError(i);
            }
            else if (!p.changed)
            {
                throw NoOperandsInParenthesesError(i);
            }
            result = p.result;
            st.emplace('*', result, false, false);
            return true;
        }
    }
    else
    {
        throw TooManyClosingParenthesesError(i);
    }
}

TokenType GetNextOpToken(int& i, const string& expr)
{
    switch(expr[i])
    {
        case ' ':
        case '\t':
            return TokenType::Space;
        case '+':
            return TokenType::Plus;
        case '*':
            return TokenType::Star;
        default:
            throw NoOperatorError(i);
    }
}
TokenType LookAheadForOpToken(int& i, const string& expr)
{
    int j;
    for (j = i; j < expr.length(); j++)
    {
        TokenType token = GetNextOpToken(j, expr);
        switch (token) {
            case TokenType::Space:
                continue;
            default:
                i = j;
                return token;
        }
    }
    i = j;
    throw NoOperatorError(i);
}

long long GetNumber( const string &expr, int &i) {
    long long num = 0;
    while (i < expr.length() && isdigit(expr[i]))
    {
        if ((LLONG_MAX - (expr[i] - '0')) / 10 >= num)
        {
            num = num * 10 + (expr[i] - '0');
        }
        else
        {
            throw TooLargeNumberError(i);
        }
        i++;
    }
    i--;
    return num;
}


pair<TokenType, long long> GetNextToken(const string& expr, int& i)
{
    switch(expr[i])
    {
        case ' ':
        case '\t':
            return {TokenType::Space, 0};
        case '(':
            i++;
            return {LookAheadForOpToken(i, expr), 0};
        case ')':
            return {TokenType::CloseParenthesis, 0};
        case '-':
            return {TokenType::Minus, 0};
        case '+':
        case '*':
            throw NoOpeningParenthesisError(i);
        default:
            if (isdigit(expr[i]))
            {

                return {TokenType::Digit, GetNumber(expr, i)};
            }
            else
            {
                throw InvalidCharacterError(i);
            }
    }
}
//todo подумать как сделать покороче

bool ProcessNextToken(pair<TokenType, long long> tokenWithNumber, stack<Layer>& st, int i)
{
    long long result = 0;
    switch (tokenWithNumber.first) {
        case TokenType::CloseParenthesis:
            if (PopStack(st, result, i))
            {
                return true;
            }
            break;
        case TokenType::Minus:
            st.top().isNegative = true;
            break;
        case TokenType::Star:
            st.emplace('*', 1, false, false);
            break;
        case TokenType::Plus:
            st.emplace('+', 0, false, false);
            break;
        case TokenType::Digit:
            if (!st.empty())
            {
                st.top().changed = true;
                ExecuteAnOperation(st.top(), tokenWithNumber.second);
            }
            else
            {
                throw NumberOutsideTheParenthesesError(i);
            }
        case TokenType::Space:
            break;
    }
    return false;
}

long long EvaluateExpression(const string& expr)
{
    stack<Layer> st;
    int i;
    for (i = 0; i < expr.length(); i++)
    {
        pair<TokenType, long long> tokenWithNumber = GetNextToken(expr, i);
        if (ProcessNextToken(tokenWithNumber, st, i))
        {
            return st.top().result;
        }
    }
    throw NoClosingParenthesesError(i);
}





//
//bool LookAheadForOp(int& i, const string& expr, stack<Layer>& st)
//{
//    for (int j = i + 1; j < expr.length(); j++)
//    {
//        if (expr[j] == ' ')
//        {
//            continue;
//        }
//        if (expr[j] == '+')
//        {
//            st.emplace('+', 0, false, false);
//            i = j;
//            return true;
//        }
//        else if (expr[j] == '*')
//        {
//            st.emplace('*', 1, false, false);
//            i = j;
//            return true;
//        }
//        return false;
//    }
//    return false;
//}
//

//
//void GetInteger(stack<Layer> &st, const string &expr, int &i) {
//    long long num = 0;
//    while (i < expr.length() && isdigit(expr[i]))
//    {
//        if ((LLONG_MAX - (expr[i] - '0')) / 10 > num)
//        {
//            num = num * 10 + (expr[i] - '0');
//        }
//        else
//        {
//            throw TooLargeNumberError();
//        }
//        i++;
//    }
//    i--;
//    if (!st.empty())
//    {
//        ExecuteAnOperation(st.top(), num);
//    }
//    else
//    {
//        throw NumberOutsideTheParenthesesError();
//    }
//}
//
//long long EvaluateExpression2(const string& expr)
//{
//    stack<Layer> st;
//    for (int i = 0; i < expr.length(); i++)
//    {
//        if (expr[i] == ' ' or expr[i] == '\t')
//        {
//            continue;
//        }
//        else if (expr[i] == '(')
//        {
//            if (!LookAheadForOp(i, expr, st))
//            {
//                throw NoOperatorError();
//            }
//        }
//        else if (expr[i] == ')')
//        {
//            long long result = 0;
//            if (PopStack(st, result))
//            {
//                return result;
//            }
//        }
//        else if (isdigit(expr[i]))
//        {
//            GetInteger(st, expr, i);
//        }
//        else if (expr[i] == '-')
//        {
//            st.top().isNegative = true;
//        }
//        else if (expr[i] == '+' or expr[i] == '*')
//        {
//            throw NoOpeningParenthesisError();
//        }
//        else
//        {
//            throw InvalidCharacterError();
//        }
//    }
//    throw NotEnoughClosingParenthesesError();
//}
//

