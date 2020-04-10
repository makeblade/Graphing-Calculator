#include "token.h"

/**
 * @brief Token::Token constructor
 * @param tok_str
 * @param type
 */
Token::Token(string tok_str, int type)
{
    _str = tok_str;
    _type = type;
}

void Token::print() const
{

}
