#include "operator.h"

/**
 * @brief Operator::Operator
 *  check the given operator's precedence
 * @param op
 */
Operator::Operator(string op)
    :Token(op, 2)
{
    _op = op;
    if(op == "(" || op == ")")  // Parethesis has the highest
        _prec = 1;
    else if(op == "sin" || op == "cos" || op == "tan" || op == "ln"
            || op == "log" || op == "arcsin" || op == "arccos" || op == "arctan"
            || op == "sinh" || op == "cosh" || op == "tanh" || op == "abs"
            || op == "sqrt")
        _prec = 2;
    else if(op == "^")
        _prec = 3;
    else if(op == "*" || op == "/")
        _prec = 4;
    else
        _prec = 5;
}

/**
 * @brief Operator::getType get type of the token
 * @return the type
 */
int Operator::getType()
{
    return 2;
}

/**
 * @brief Operator::print the content
 */
void Operator::print() const
{
    cout << _op;
}

/**
 * @brief Operator::op
 * @return the operator
 */
string Operator::op()
{
    return _op;
}

/**
 * @brief Operator::prec
 * @return the precedence of the operator
 */
int Operator::prec()
{
    return _prec;
}
