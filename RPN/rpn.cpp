#include "rpn.h"


RPN::RPN():_postfix(){}

/**
 * @brief RPN::RPN constructor
 * @param postfix
 */
RPN::RPN(const Queue<Token*>& postfix)
{
    _postfix = postfix;
}

/**
 * @brief RPN::evaluate a given value with reverse polish notation
 * @param value
 * @return the result
 */
float RPN::evaluate(float value)
{
    Queue<Token*> temp = _postfix;  // post fix caluclated with shuntingyard
    Stack<float> result;            // result stack
    float cal_result = 0;           //  temp stores result
    string cal_operator;            // temp stores operator

    while(!temp.empty())
    {
        // check the type first
        switch (temp.front().operator*()->getType()) {
        case 1:
            // if its number, push to result stack
            result.push(static_cast<float>(static_cast<Number*>(
                                            temp.front().operator*())->Num()));
            break;
        case 2:
            // if its is operator, calculator the number in result stack with
            //  current operator
            cal_operator = static_cast<Operator*>
                    (temp.front().operator*())->op();

            if(cal_operator == "+")
                cal_result = result.pop() + result.pop();
            else if(cal_operator == "-")
            {
                float i = result.pop();
                if(result.empty())
                    cal_result = 0 - i;
                else
                    cal_result =  result.pop() - i;
            }
            else if(cal_operator == "*")
                cal_result = result.pop() * result.pop();
            else if(cal_operator == "/")
                cal_result = 1 / result.pop() * result.pop();
            else if(cal_operator == "^")
                cal_result = pow(result.pop(),result.pop());
            else if(cal_operator == "sin")
                cal_result = sin(result.pop());
            else if(cal_operator == "cos")
                cal_result = cos(result.pop());
            else if(cal_operator == "tan")
                cal_result = tan(result.pop());
            else if(cal_operator == "ln")
                cal_result = log(result.pop());
            else if(cal_operator == "log")
                cal_result = log10(result.pop());
            else if(cal_operator == "arcsin")
                cal_result = asin(result.pop());
            else if(cal_operator == "arccos")
                cal_result = acos(result.pop());
            else if(cal_operator == "arctan")
                cal_result = atan(result.pop());
            else if(cal_operator == "sinh")
                cal_result = sinh(result.pop());
            else if(cal_operator == "cosh")
                cal_result = cosh(result.pop());
            else if(cal_operator == "tanh")
                cal_result = tanh(result.pop());
            else if(cal_operator == "sqrt")
                cal_result = sqrt(result.pop());
            else if(cal_operator == "abs")
                cal_result = abs(result.pop());
            result.push(cal_result);
            break;
        case 3:
            result.push(value);
        }
        // opop the used token
        temp.pop();
    }
    // return the final result
    return *(result.bottom());
}
