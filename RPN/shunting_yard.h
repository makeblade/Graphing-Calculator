#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H
#include "rpn.h"

class shuntingYard
{
public:
    shuntingYard();
    shuntingYard(string equation);

    Queue<Token*> infix(string str);
    Queue<Token*> postFix();

    Queue<Token*> equation();
    void set_equation(Queue<Token*>);
    bool isInteger(char c);

private:
    Queue<Token*> _equation;
};

#endif // SHUNTING_YARD_H
