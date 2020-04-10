#include "term.h"

//------------------------------constructor-------------------------------------
/**
 * @brief Term::Term
 *  constructor initailize fields with given parameter
 * @param coef
 * @param exp
 */
Term::Term(double coef, int exp)
{
    this->_coef = coef;
    this->_exp = exp;
}

//------------------------------utility-----------------------------------------
/**
 * @brief Term::compare
 *  copares this term with a given term
 * @param t
 * @return true of given terms is same as this term, false otherwise
 */
bool Term::compare(const Term& t) const
{
    // if their coef as a difference less than specifie number, ignoret the diff
    return abs(this->_coef - t._coef) < 0.00001;
}

//------------------------------operator overload-------------------------------


Term& Term::operator +=(const Term& rhs)
{
    assert(rhs._exp == _exp);
    _coef += rhs._coef;
    return *this;
}

Term& Term::operator -=(const Term& rhs)
{
    assert(rhs._exp == _exp);
    _coef -= rhs._coef;
    return *this;
}

Term& Term::operator *=(const Term& rhs)
{
    _exp += rhs._exp;
    _coef *= rhs._coef;
    return *this;
}

Term& Term::operator /=(const Term& rhs)
{
    _exp -= rhs._exp;
    _coef /= rhs._coef;
    return *this;
}


/**
 * @brief operator ==
 *  comparison operator overload between terms
 * @param lhs
 * @param rhs
 * @return  true of given two terms are same, false otherwise
 */
bool operator ==(const Term& lhs, const Term& rhs)
{
    return lhs._exp == rhs._exp;
}

/**
 * @brief operator !=
 *  not equals comparison operator overload between terms
 * @param lhs
 * @param rhs
 * @return  false if given terms are same, true otherwise
 */
bool operator !=(const Term& lhs, const Term& rhs)
{
    return !(lhs == rhs);
}

/**
 * @brief operator >
 *  greatre operator overload between terms
 * @param lhs
 * @param rhs
 * @return   true of given lhs greater than rhs term, false otherwise
 */
bool operator >(const Term& lhs, const Term& rhs)
{
    return lhs._exp > rhs._exp;
}

/**
 * @brief operator <
 *  greatre operator overload between terms
 * @param lhs
 * @param rhs
 * @return   true of given lhs greater than rhs term, false otherwise
 */
bool operator <(const Term& lhs, const Term& rhs)
{
    return lhs._exp < rhs._exp;
}

/**
 * @brief operator /
 *  division operator overload for terms
 * @param lhs
 * @param rhs
 * @return quotien of given two terms
 */
Term operator / (const Term& lhs, const Term& rhs)
{
    return Term(lhs._coef/rhs._coef, lhs._exp-rhs._exp);
}

/**
 * @brief operator *
 *  multiplication operator overload
 * @param lhs
 * @param rhs
 * @return the product of given two terms
 */
Term operator * (const Term& lhs, const Term& rhs)
{
    return Term(lhs._coef*rhs._coef, lhs._exp+rhs._exp);
}

//----------------------------insertion/extraction------------------------------

/**
 * @brief operator <<
 *  insertion operator overload for term
 * @param outs
 * @param t
 * @return  ostream
 */
ostream& operator <<(ostream& outs, const Term& t)
{
    // print only terms with non-zero coef
    if(t._coef != 0.0)
    {
        if(t._coef>0) cout << " +";
        else cout << " ";
        if(t._exp == 0)
            cout << fixed << showpoint << setprecision(1) << t._coef;
        else
            cout << fixed << showpoint << setprecision(1) <<
                    t._coef << "X^" << noshowpoint << t._exp;
    }
    return outs;
}

/**
 * @brief operator >>
 *  extraction operator overload for term
 * @param ins
 * @param t
 * @return istream
 */
istream& operator >>(istream& ins, Term& t)
{
    // this char catches X
    char x;
    ins >> t._coef >> x >> t._exp;
    return ins;
}

/**
 * @brief operator -
 * @param t
 * @return negative of term
 */
Term operator -(const Term& t)
{
    return Term(-1*t._coef, t._exp);
}
