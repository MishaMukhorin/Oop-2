//
// Created by Misha on 22.02.2024.
//

#ifndef OOP_2_EVALUATEEXPRERRORS_H
#define OOP_2_EVALUATEEXPRERRORS_H

#include <stdexcept>

//todo базовый класс исключений от runtime error и хранить позицию в нем
class NoNumberAfterMinusError : public std::invalid_argument {
public:
    explicit NoNumberAfterMinusError(int position) : std::invalid_argument(""), _position(position) {}

    [[nodiscard]] int getPosition() const {
        return _position;
    }

private:
    int _position;
};
//                "Invalid input: No number after minus!"


class NoOperandsInParenthesesError : public std::invalid_argument {
public:
    explicit NoOperandsInParenthesesError(int position) : std::invalid_argument(""), _position(position) {}
// todo с заглавной
    [[nodiscard]] int getPosition() const {
        return _position;
    }

private:
    int _position;
};
//                "Invalid input: There must be at least one operand in parentheses!"


class TooManyClosingParenthesesError : public std::invalid_argument {
public:
    explicit TooManyClosingParenthesesError(int position) : std::invalid_argument(""), _position(position) {}

    [[nodiscard]] int getPosition() const {
        return _position;
    }

private:
    int _position;
};
//        "Invalid input: too many \")\"!"


class TooLargeNumberError : public std::invalid_argument {
public:
    explicit TooLargeNumberError(int position) : std::invalid_argument(""), _position(position) {}

    [[nodiscard]] int getPosition() const {
        return _position;
    }

private:
    int _position;
};
//            "Invalid input: Too large number!"


class NumberOutsideTheParenthesesError : public std::invalid_argument {
public:
    explicit NumberOutsideTheParenthesesError(int position) : std::invalid_argument(""), _position(position) {}

    [[nodiscard]] int getPosition() const {
        return _position;
    }

private:
    int _position;
};
//        "Invalid input: there is a number outside the parentheses!"


class NoOperatorError : public std::invalid_argument {
public:
    explicit NoOperatorError(int position) : std::invalid_argument(""), _position(position) {}

    [[nodiscard]] int getPosition() const {
        return _position;
    }

private:
    int _position;
};
//                "Invalid input: after \"(\" should be an operator!"


class NoOpeningParenthesisError : public std::invalid_argument {
public:
    explicit NoOpeningParenthesisError(int position) : std::invalid_argument(""), _position(position) {}

    [[nodiscard]] int getPosition() const {
        return _position;
    }

private:
    int _position;
};
//           "Invalid input: there is no \"(\" in front of an operator!"

class InvalidCharacterError : public std::invalid_argument {
public:
    explicit InvalidCharacterError(int position) : std::invalid_argument(""), _position(position) {}

    [[nodiscard]] int getPosition() const {
        return _position;
    }

private:
    int _position;
};
//            "Invalid input: invalid character!"


class NoClosingParenthesesError : public std::invalid_argument {
public:
    explicit NoClosingParenthesesError(int position) : std::invalid_argument(""), _position(position) {}

    [[nodiscard]] int getPosition() const {
        return _position;
    }

private:
    int _position;
};
//    "Invalid input: not enough \")\"!"






#endif //OOP_2_EVALUATEEXPRERRORS_H
