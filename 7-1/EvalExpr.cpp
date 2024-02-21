#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <sstream>

using namespace std;


std::string eval(const std::string& expr)
{
    std::queue<std::queue<int>> subexpressions;
}

std::string EvaluateExpression(const std::string& expr)
{
    std::stack<std::stack<int>> subexprs;
    std::stack<int> operands;
    std::istringstream iss(expr);
    std::string token;
    while (iss >> token)
    {
        if (token.empty())
        {
            continue;
        }
        char ch = token[0];
        if (std::isdigit(ch) || ch == '-')
        {
            try
            {
                int num = std::stoi(token);
                if (subexprs.empty())
                {
                    operands.push(num);
                } else
                {
                    subexprs.top().push(num);
                }
            } catch (const std::invalid_argument&)
            {
                return "ERROR: invalid operand";
            } catch (const std::out_of_range&)
            {
                return "ERROR: invalid operand";
            }
        }
        else if (ch == '+')
        {
            if (subexprs.empty())
            {
                return "ERROR: not enough operands";
            }
            std::stack<int>& subexpr = subexprs.top();
            if (subexpr.empty())
            {
                return "ERROR: not enough operands";
            }
            int result = subexpr.top();
            subexpr.pop();
            while (!subexpr.empty())
            {
                int operand = subexpr.top();
                subexpr.pop();
                result += operand;
            }
            operands.push(result);
        }
        else if (ch == '*')
        {
            if (subexprs.empty())
            {
                return "ERROR: not enough operands";
            }
            std::stack<int>& subexpr = subexprs.top();
            if (subexpr.empty())
            {
                return "ERROR: not enough operands";
            }
            int result = subexpr.top();
            subexpr.pop();
            while (!subexpr.empty())
            {
                int operand = subexpr.top();
                subexpr.pop();
                result *= operand;
            }
            operands.push(result);
        }
        else if (ch == '(')
        {
            subexprs.push(std::stack<int>());
        }
        else if (ch == ')')
        {
            if (subexprs.empty())
            {
                return "ERROR: too many closing parentheses";
            }
            std::stack<int> subexpr = subexprs.top();
            subexprs.pop();
            if (subexpr.empty())
            {
                return "ERROR: empty subexpression";
            }
            if (subexprs.empty())
            {
                return "ERROR: too many operands";
            }
            subexprs.top().push(subexpr.top());
        }
        else
        {
            return "ERROR: invalid character";
        }
    }
    if (!subexprs.empty())
    {
        return "ERROR: too many opening parentheses";
    }
    if (operands.size() != 1)
    {
        return "ERROR: too many operands";
    }
    return std::to_string(operands.top());
}

int main()
{
    std::string expr;
    while (getline(cin, expr))
    {
        cout << EvaluateExpression(expr) << '\n';
    }
    return 0;
}