
#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>
#include "List.h"
#include "BigInteger.h"

using namespace std;

int main () {
    BigInteger A, B, C, D;
    A = BigInteger("12345");
    B = BigInteger("11111");
    C = BigInteger();
    D = BigInteger("12345678910");
    cout << "A's sign is : " << A.sign() << "\n";
    cout << "A : " << A << "\n";
    cout << "B : " << B << "\n";
    cout << "A + B = " << A+B << "\n";
    cout << "A - B = " << A-B << "\n";  
    if (A < D) {
        cout << "A < D\n";
    } else {
        cout << "A <= D\n";
    } 
    A.makeZero();
    if (A == C) {
        cout << "A is empty now\n";
    }
    B.negate();
    cout << "-B : " << B << "\n";
    return 0;
}




