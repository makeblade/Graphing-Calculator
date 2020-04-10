#include "shunting_yard.h"


shuntingYard::shuntingYard():_equation(){}

/**
 * @brief shuntingYard::shuntingYard constructor
 * @param equation
 */
shuntingYard::shuntingYard(string equation)
{
    _equation = infix(equation);
}

/**
 * @brief shuntingYard::infix
 * @param str
 * @return given a equation string, return a infix
 */
Queue<Token*> shuntingYard::infix(string str)
{
    Queue<Token*> result;
    string temp;

    // check each character in the string
    for(unsigned int i=0; i<str.length(); i++)
    {
        // if it is a int, check if it is a decimal
        if(isInteger(str.at(i)))
        {
            temp = "";
            temp += str.at(i);
            while(i+1 < str.length() && isInteger(str.at(i+1)))
                temp += str.at(++i);

            result.push(new Number(temp));
        }
        // check for special charactor
        else if(str.at(i) == 'e')
        {
            result.push(new Number(exp(1)));
        }
        // check if it is something like 3x
        else if(str.at(i) == 'x')
        {
            if(i != 0 && isInteger(str.at(i-1)))
                result.push(new Operator("*"));
            result.push(new Variable("x"));
        }
        // other posible function operator
        else
        {
            switch(tolower(str.at(i)))
            {
            case 's':
                if(str.at(i+3) == 'h')
                {
                    result.push(new Operator("sinh"));
                    i+=3;
                    break;
                }
                else if(str.at(i+1) == 'q')
                {
                    result.push(new Operator("sqrt"));
                    i+=3;
                    break;
                }
                else
                    result.push(new Operator("sin"));
                i+=2;
                break;
            case 'c':
                if(str.at(i+3) == 'h')
                {
                    result.push(new Operator("cosh"));
                    i+=3;
                    break;
                }
                else
                    result.push(new Operator("cos"));
                i+=2;
                break;
            case 't':
                if(str.at(i+3) == 'h')
                {
                    result.push(new Operator("tanh"));
                    i+=3;
                    break;
                }
                else
                    result.push(new Operator("tan"));
                i+=2;
                break;
            case 'a':
                if(str.at(i+1) == 'b')
                {
                    result.push(new Operator("abs"));
                    i+=2;
                    break;
                }
                if(str.at(i+3) == 's')
                    result.push(new Operator("arcsin"));
                else if(str.at(i+3) == 'c')
                    result.push(new Operator("arccos"));
                else
                    result.push(new Operator("arctan"));
                i+=5;
                break;
            case 'l':
                if(str.at(i+1) == 'o')
                {
                    result.push(new Operator("log"));
                    i+=2;
                }
                else
                {
                    result.push(new Operator("ln"));
                    i+=1;
                }
                break;
            case 'P':
                result.push(new Number(M_PI));
                i+=1;
                break;
            case ' ': break;
            default:
                // if it is a single char operator, push it
                result.push(new Operator(string(1, str.at(i))));
            }
        }
    }

    _equation = result;
    return result;
}

/**
 * @brief shuntingYard::postFix convert the infix to post fix
 * @return postfix
 */
Queue<Token*> shuntingYard::postFix()
{
    // stores operators
    Stack<Operator*> operators;
    Queue<Token*> output;

    // go through every token in the queue
    for(Queue<Token*>::Iterator it=_equation.front(); it!=nullptr; it++)
    {
        // check if it is number or variable
        if((*it)->getType() == 1 || (*it)->getType() == 3)
            output.push(*it);
        // if it is operator, check its precedence
        else if((*it)->getType() == 2)
        {
            if(static_cast<Operator*>(*it)->prec() == 1)
            {
                // if given a open parenthesis, just push it in
                if(static_cast<Operator*>(*it)->op() == "(")
                    operators.push(static_cast<Operator*>(*it));
                // if it is close, take all the token pushed until find the last
                //  opern parenthesis
                else
                {
                    while((*operators.top())->op() != "(")
                    {
                        output.push(operators.pop());
                    }
                    operators.pop();
                }
            }
            else
            {
                // else if precedence is small or same, also pop the operatos
                while(!operators.empty() && (*operators.top())->prec() <=
                      static_cast<Operator*>(*it)->prec()
                      && (*operators.top())->prec() != 1)
                {
                    output.push(operators.pop());
                }
                operators.push(static_cast<Operator*>(*it));
            }
        }
    }
    // the remaining operator in stack will attatch to the list
    while(!operators.empty())
    {
        output.push(operators.pop());
    }

    return output;

}

/**
 * @brief shuntingYard::isInteger
 * @param c
 * @return  if given char is a int
 */
bool shuntingYard::isInteger(char c)
{
    return (c >= 48 && c <= 57) || c == 46;
}

/**
 * @brief shuntingYard::equation
 * @return _equation
 */
Queue<Token*> shuntingYard::equation()
{
    return _equation;
}

/**
 * @brief shuntingYard::set_equation
 *  _equation mutator
 * @param e
 */
void shuntingYard::set_equation(Queue<Token*> e)
{
    _equation = e;
}
