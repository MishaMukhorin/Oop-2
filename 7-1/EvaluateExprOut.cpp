//
// Created by Misha on 21.02.2024.
//

#include "EvaluateExpr.h"
#include "EvaluateExprErrors.h"

using namespace std;

int main()
{
    string expr;
    while (getline(cin, expr))
    {
        try
        {
            cout << EvaluateExpression(expr) << '\n';
        }
        catch(const NoNumberAfterMinusError& e)
        {
            std::cerr << "Invalid input: No number after minus in position " << e.getPosition() << "!\n";
        }
        catch(const NoOperandsInParenthesesError& e)
        {
            std::cerr << "Invalid input: There must be at least one operand in parentheses in position " << e.getPosition() << "!\n";
        }
        catch(const TooManyClosingParenthesesError& e)
        {
            std::cerr << "Invalid input: too many \")\" in position " << e.getPosition() << "!\n";
        }
        catch(const TooLargeNumberError& e)
        {
            std::cerr << "Invalid input: Too large number in position " << e.getPosition() << "!\n";
        }
        catch(const NumberOutsideTheParenthesesError& e)
        {
            std::cerr << "Invalid input: there is a number outside the parentheses in position " << e.getPosition() << "!\n";
        }
        catch(const NoOperatorError& e)
        {
            std::cerr << "Invalid input: after \"(\" should be an operator in position " << e.getPosition() << "!\n";
        }
        catch(const NoOpeningParenthesisError& e)
        {
            std::cerr << "Invalid input: there is no \"(\" in front of an operator in position " << e.getPosition() << "!\n";
        }
        catch(const InvalidCharacterError& e)
        {
            std::cerr << "Invalid input: invalid character in position " << e.getPosition() << "!\n";
        }
        catch(const NoClosingParenthesesError& e)
        {
            std::cerr << "Invalid input: not enough \")\" in position " << e.getPosition() << "!\n";
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << "\n";
        }
        catch(...)
        {
            std::cerr << "Unknown error\n";
        }
    }
    return 0;
}