#ifndef EXPRESSIONPROTOCOL_H
#define EXPRESSIONPROTOCOL_H

#include <string>
#include <sstream>
#include <iostream>
#include "Fraction.h"

using std::istringstream, std::string, std::cout, std::endl;

void processInput(string line) {
    // Extract tokens
    istringstream expression(line);
    string f1;
    string operation;
    string f2;
    expression >> f1;
    expression >> operation;
    if (!(expression.eof())) {
        expression >> f2;
    }

    // Parse tokens
    Fraction frac1;
    Fraction frac2;
    try {
        istringstream f1Stream(f1);

        // Check if negative
        if (f1Stream.peek() == '-') {
            frac1.setNegBit(true);
            f1Stream.ignore(1, '-');
        }

        // Get numerator
        char f1Numerator[11];
        f1Stream.getline(f1Numerator, 10, '/');
        frac1.setNumerator(stoul(string(f1Numerator)));

        // Get denominator
        char f1Denominator[11];
        f1Stream.getline(f1Denominator, 10, ' ');
        frac1.setDenominator(stoul(string(f1Denominator)));

        if (operation.empty()) {
            // Just simplify
            frac1.simplify();
            cout << frac1 << endl;
        } else {
            istringstream f2Stream(f2);

            // Check if negative
            if (f2Stream.peek() == '-') {
                frac2.setNegBit(true);
                f2Stream.ignore(1, '-');
            }

            // Get numerator
            char f2Numerator[11];
            f2Stream.getline(f2Numerator, 10, '/');
            frac2.setNumerator(stoul(string(f2Numerator)));

            // Get denominator
            char f2Denominator[11];
            f2Stream.getline(f2Denominator, 10, ' ');
            frac2.setDenominator(stoul(string(f2Denominator)));

            // Determine operation
            if (operation == "+") {
                cout << "Answer: " << (frac1 + frac2) << endl;
            } else if (operation == "-") {
                cout << "Answer: " << (frac1 - frac2) << endl;
            } else if (operation == "*") {
                cout << "Answer: " << (frac1 * frac2) << endl;
            } else if (operation == "/") {
                cout << "Answer: " << (frac1 / frac2) << endl;
            } else {
                throw std::invalid_argument("'" + operation + "' is not a recognized operation.");
            }
        }
    } catch (std::exception e) {
        cout << e.what() << endl;
        throw std::invalid_argument("'" + line + "' is not a valid expression.");
    }
}

#endif