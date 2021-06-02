#ifndef GCD_H
#define GCD_H

/************************************************
 * Filename: gcd.h
 * Created By: Luke Loera
 * Date Started: 02/04/2021
 * Last Updated: 02/04/2021
 * 
 * Purpose: House function that finds the greatest
 * common divider
 * 
 ************************************************/

unsigned int gcd(unsigned int x, unsigned int y) {
    if (x < y) {
        return gcd(y, x);
    } else if (y == 0) {
        return x;
    } else {
        unsigned int remainder = x % y;
        return gcd(y, remainder);
    }
}

#endif