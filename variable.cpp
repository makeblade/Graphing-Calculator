#include "variable.h"

/**
 * @brief Variable::Variable constructor
 * @param v
 */
Variable::Variable(string v)
    :Token(v, 3)
{
    _v = v;
}

/**
 * @brief Variable::getType
 * @return the type of this token
 */
int Variable::getType()
{
    return 3;
}

/**
 * @brief Variable::print the variable
 */
void Variable::print() const
{
    cout << _v;
}

/**
 * @brief Variable::variable
 * @return the variable
 */
string Variable::variable()
{
    return _v;
}
