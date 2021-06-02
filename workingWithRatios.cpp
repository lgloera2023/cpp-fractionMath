#include <iostream>
#include <string>
#include "expressionProtocol.h"
using std::cout, std::cin, std::endl, std::string;

int main() {
    // Instructions
    cout << "Available Operations:" << endl;
    cout << "\tAddition: 'a/b + c/d'" << endl;
    cout << "\tSubtraction: 'a/b - c/d'" << endl;
    cout << "\tMultiplication: 'a/b * c/d'" << endl;
    cout << "\tDivision: 'a/b / c/d'" << endl;
    cout << "\tSimplification: 'a/b'" << endl;
    cout << "\n****MUST SEPARATE FRACTIONS WITH SPACES****" << endl;

    char run = 'y';

    while (tolower(run) == 'y') {
        // Get expression
        string line;
        cout << "\nEnter expression: " << endl;
        std::getline(cin, line);
        cin.clear();

        // Make calculations
        try {
            processInput(line);
        } catch (std::invalid_argument e) {
            cout << e.what() << endl;
        }

        // Get next input
        cout << "\nDo you want to make another calculation? (y/n)\t" << endl;
        cin >> run;
        cin.ignore();
        cin.clear();
    }

    return 0;
}
