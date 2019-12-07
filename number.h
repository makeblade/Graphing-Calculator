#ifndef NUMBER_H
#define NUMBER_H
#include "token.h"

class Number:public Token
{
public:
    Number(double num);
    Number(string num);

    int getType();
    void print() const;
    double Num();
private:
    double _num;

};


#endif // NUMBER_H
