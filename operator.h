#ifndef OPERATOR_H
#define OPERATOR_H
#include "token.h"

class Operator:public Token
{
public:
    Operator(string op);

    int getType();
    void print() const;
    string op();

    virtual int prec();
private:
    string _op;
    int _prec;

};

#endif // OPERATOR_H
