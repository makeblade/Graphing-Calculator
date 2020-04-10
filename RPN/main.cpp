#include <iostream>
#include "shunting_yard.h"
#include "../../include/myvector.h"

using namespace std;

int main()  // -------------------------main------------------------------------
{
    shuntingYard sy("sin(x)");

    cout << sy.postFix() << endl;


    //RPN rpn(sy.postFix());

    //cout << rpn.evaluate() << endl;



    return 0;
}
