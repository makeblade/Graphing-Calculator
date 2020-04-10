#ifndef RPN_H
#define RPN_H
#include <cmath>
#include "number.h"
#include "operator.h"
#include "variable.h"
#include "../../include/myqueue.h"
#include "../../include/MyStack.h"
#include "../../include/myvector.h"

class RPN
{
public:
    RPN();
    RPN(const Queue<Token*>& postfix);

    float evaluate(float value = 0);

private:
    Queue<Token*> _postfix;

};


#endif // RPN_H
