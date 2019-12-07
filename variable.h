#ifndef VARIABLE_H
#define VARIABLE_H
#include "token.h"

class Variable:public Token
{

public:
    Variable(string op);

    int getType();
    void print() const;
    string variable();

private:
    string _v;

};


#endif // VARIABLE_H
