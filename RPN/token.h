#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>

using namespace std;

class Token
{
public:
    virtual ~Token(){}

    Token(string tok_str, int type);
    virtual int getType(){return 0;}
    virtual void print() const;

    friend ostream& operator << (ostream& outs, Token* t)
    {
        t->print();
        return outs;
    }
private:
    string _str;
    int _type;
};


#endif // TOKEN_H
