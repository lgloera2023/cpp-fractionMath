#ifndef FRACTION_H
#define FRACTION_H

/************************************************
 * Filename: Fraction.h
 * Created By: Luke Loera
 * Date Started: 02/04/2021
 * Last Updated: 02/04/2021
 * 
 * Purpose: Class and helper function declarations. 
 * 
 ************************************************/

#include <iostream>
#include "gcd.h"

class Fraction {
    private:
        // Using two unsigned integers and a negative indicator allows more precision
        unsigned int numerator;
        unsigned int denominator;
        bool negBit;
    public:
        Fraction();
        Fraction(unsigned int numerator, unsigned int denominator, bool negative = false);
        unsigned int getNumerator();
        unsigned int getDenominator();
        bool isNegative();
        void setNumerator(unsigned int num);
        void setDenominator(unsigned int num);
        void setNegBit(bool negative);
        void simplify();
};



/////////////////////////////////////////////////
//             Default Constructor             //
/////////////////////////////////////////////////
Fraction::Fraction() {
    numerator = 0;
    denominator = 0;
    negBit = false;
}



/////////////////////////////////////////////////
//                 Constructor                 //
/////////////////////////////////////////////////
Fraction::Fraction(unsigned int numerator, unsigned int denominator, bool negative) {
    this->numerator = numerator;
    this->denominator = denominator;
    negBit = negative;
}



/////////////////////////////////////////////////
//                Get Numerator                //
/////////////////////////////////////////////////
unsigned int Fraction::getNumerator() {
    return numerator;
}



/////////////////////////////////////////////////
//               Get Denominator               //
/////////////////////////////////////////////////
unsigned int Fraction::getDenominator() {
    return denominator;
}



/////////////////////////////////////////////////
//                 Is Negative                 //
/////////////////////////////////////////////////
bool Fraction::isNegative() {
    return negBit;
}



/////////////////////////////////////////////////
//                Set Numerator                //
/////////////////////////////////////////////////
void Fraction::setNumerator(unsigned int num) {
    numerator = num;
}



/////////////////////////////////////////////////
//               Set Denominator               //
/////////////////////////////////////////////////
void Fraction::setDenominator(unsigned int num) {
    denominator = num;
}



/////////////////////////////////////////////////
//                 Set NegBit                  //
/////////////////////////////////////////////////
void Fraction::setNegBit(bool negative) {
    negBit = negative;
}



/////////////////////////////////////////////////
//                  Simplify                   //
/////////////////////////////////////////////////
void Fraction::simplify() {
    // Find greatest common factor
    unsigned int factor = gcd(numerator, denominator);
    if (factor != 1) {
        // Not simplified
        numerator /= factor;
        denominator /= factor;
    }
}



/////////////////////////////////////////////////
//                 Operator<<                  //
/////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, Fraction frac) {
    // Determine if negative
    if (frac.isNegative()) {
        os << "-";
    }
    // Ex:
    // numerator = 3, denominator = 4, negBit = false =>  "3/4"
    // numerator = 3, denominator = 4, negBit = true =>  "-3/4"
    os << frac.getNumerator() << "/" << frac.getDenominator();

    return os;
}



/////////////////////////////////////////////////
//                 Operator+                   //
/////////////////////////////////////////////////
Fraction operator+(Fraction frac1, Fraction frac2) {
    // Cross multiply
    // frac1 = x/z, frac2 = y/z
    unsigned int x = frac1.getNumerator() * frac2.getDenominator();
    unsigned int y = frac2.getNumerator() * frac1.getDenominator();
    unsigned int z = frac1.getDenominator() * frac2.getDenominator();

    // Create new fraction with sum of numerators and new denominator
    Fraction sum;
    sum.setDenominator(z);  // This will be the same no matter what
    if (frac1.isNegative()) {
        if (frac2.isNegative()) {
            // Two negative numbers
            sum.setNumerator(x + y);
            sum.setNegBit(true);
        } else {
            if (x > y) {
                // Result is negative
                sum.setNumerator(x - y);
                sum.setNegBit(true);
            } else {
                // Result is positive
                sum.setNumerator(y - x);  // Avoid unsigned rollover
            }
        }
    } else {
        if (frac2.isNegative()) {
            if (x > y) {
                // Result is positive
                sum.setNumerator(x - y);
            } else {
                // Result is negative
                sum.setNumerator(y - x);  // Avoid unsigned rollover
                sum.setNegBit(true);
            }
        } else {
            // Two positive numbers
            sum.setNumerator(x + y);
        }
    }

    // Simplify
    sum.simplify();

    return sum;
}



/////////////////////////////////////////////////
//                 Operator-                   //
/////////////////////////////////////////////////
Fraction operator-(Fraction frac1, Fraction frac2) {
    // Switch sign of second and add
    if (frac2.isNegative()) {
        frac2.setNegBit(false);
    } else {
        frac2.setNegBit(true);
    }

    return frac1 + frac2;
}



/////////////////////////////////////////////////
//                 Operator*                   //
/////////////////////////////////////////////////
Fraction operator*(Fraction frac1, Fraction frac2) {
    // Multiply numerator by numerator and denominator by denominator
    Fraction product;
    product.setNumerator(frac1.getNumerator() * frac2.getNumerator());
    product.setDenominator(frac1.getDenominator() * frac2.getDenominator());
    // Check signs
    if (frac1.isNegative()) {
        if (!(frac2.isNegative())) {
            // Negative
            product.setNegBit(true);
        }
    } else {
        if (frac2.isNegative()) {
            // Negative
            product.setNegBit(true);
        }
    }

    // Simplify
    product.simplify();

    return product;
}



/////////////////////////////////////////////////
//                 Operator/                   //
/////////////////////////////////////////////////
Fraction operator/(Fraction frac1, Fraction frac2) {
    // Flip frac2's numerator and denominator and multiply
    unsigned int tmp = frac2.getNumerator();
    frac2.setNumerator(frac2.getDenominator());
    frac2.setDenominator(tmp);

    return frac1 * frac2;
}



/////////////////////////////////////////////////
//                 Operator==                  //
/////////////////////////////////////////////////
bool operator==(Fraction frac1, Fraction frac2) {
    bool isEqual = frac1.getNumerator() == frac2.getNumerator();
    isEqual = isEqual && (frac1.getDenominator() == frac2.getDenominator());
    return isEqual && (frac1.isNegative() == frac2.isNegative());
}



/////////////////////////////////////////////////
//                 Operator!=                  //
/////////////////////////////////////////////////
bool operator!=(Fraction frac1, Fraction frac2) {
    return !(frac1 == frac2);
}



/////////////////////////////////////////////////
//                 Operator<                   //
/////////////////////////////////////////////////
bool operator<(Fraction frac1, Fraction frac2) {
    bool less = false;
    Fraction tmp = frac1 - frac2;
    if (frac1.isNegative()) {
        if (frac2.isNegative()) {
            // If both negative, subtract. False if negative.
            if (!(tmp.isNegative())) {
                less = true;
            }
        }
        // If frac1 is negative and frac2 is positive, true.
    } else {
        if (!(frac2.isNegative())) {
            // If both positive, subtract. True if negative.
            if (tmp.isNegative()) {
                less = true;
            }
        }
        // If frac1 is positive and frac2 is negative, false
    }
    
    return less;
}



/////////////////////////////////////////////////
//                 Operator<=                   //
/////////////////////////////////////////////////
bool operator<=(Fraction frac1, Fraction frac2) {
    return (frac1 < frac2) || (frac1 == frac2);
}



/////////////////////////////////////////////////
//                 Operator>                   //
/////////////////////////////////////////////////
bool operator>(Fraction frac1, Fraction frac2) {
    return !(frac1 <= frac2);
}



/////////////////////////////////////////////////
//                 Operator>=                   //
/////////////////////////////////////////////////
bool operator>=(Fraction frac1, Fraction frac2) {
    return !(frac1 < frac2);
}

#endif