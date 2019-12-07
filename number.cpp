#include "number.h"

/**
 * @brief Number::Number constructor
 * @param num
 */
Number::Number(double num)
    :Token(to_string(num), 1)
{
    _num = num;
}

/**
 * @brief Number::Number constructor
 * @param num
 */
Number::Number(string num)
    :Token(num, 1)
{
    _num = stod(num);
}

/**
 * @brief Number::getType gettype of the token
 * @return the type
 */
int Number::getType()
{
    return 1;
}

/**
 * @brief Number::print the content
 */
void Number::print() const
{
    cout << _num;
}

/**
 * @brief Number::Num return the number
 * @return the actual value of the number
 */
double Number::Num()
{
    return _num;
}
