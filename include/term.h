#ifndef TERM_H
#define TERM_H
#include "../../../include/one_d_array.h"

struct Term{
    double _coef;
    int _exp;

    Term(double coef = 0, int exp = 0);
    bool compare(const Term& t) const;

    Term& operator +=(const Term& rhs);
    Term& operator -=(const Term& rhs);
    Term& operator *=(const Term& rhs);
    Term& operator /=(const Term& rhs);

    friend bool operator ==(const Term& lhs, const Term& rhs);
    friend bool operator !=(const Term& lhs, const Term& rhs);
    friend bool operator >(const Term& lhs, const Term& rhs);
    friend bool operator <(const Term& lhs, const Term& rhs);

    //used in Poly division operator
    friend Term operator / (const Term& lhs, const Term& rhs);
    friend Term operator * (const Term& lhs, const Term& rhs);

    friend ostream& operator <<(ostream& outs, const Term& t);
    friend istream& operator >>(istream& ins, Term& t);

    friend Term operator -(const Term& t);
};


#endif // TERM_H
