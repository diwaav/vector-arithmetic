/********************************************************************************* 
* Diwa Ashwini Vittala, dashwini
* 2022 Spring CSE101 PA6
* BigInteger.cpp
* BigInteger ADT
**********************************************************************************/

#include <string>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "List.h"
#include "BigInteger.h"

// int power = 3;
int power = 9;
long base = pow(10, power); // base = 1000000000;

/*** Constructors and Destructors ***/
// BigInteger(): Constructor that creates a new BigInteger 
// in the zero state: signum=0, digits=().
BigInteger::BigInteger() {
    signum = 0;
}

BigInteger::BigInteger(std::string s) {
    if (s.empty()) {
        throw std::invalid_argument("BigInteger: BigInteger(): String is empty.\n");
    }

    if (s[0] == '+') {
        signum = 1;
        s = s.substr(1);
    } else if (s[0] == '-') {
        signum = -1;
        s = s.substr(1);
    } else {
        signum = 1;
    }

    while((s.length() % power) != 0) {
        s = "0" + s;
    }

    int l = s.length();
    for (int i = 0; i < l; i += power) {
        digits.insertBefore(stol(s.substr(0, power)));
        s = s.substr(power);
    }
}

// copy constructor
BigInteger::BigInteger(const BigInteger& N) {
    signum = 0;
    digits = N.digits;
}


/*** Access Functions ***/
int BigInteger::sign() const {
    return signum;
}

int BigInteger::compare(const BigInteger& N) const {
    if (signum > N.signum) {
        return 1;
    } else if (signum < N.signum) {
        return -1;
    }

    List a = digits;
    List b = N.digits;
    if (a.length() > b.length()) {
        return 1;
    } else if (a.length() < b.length()) {
        return -1;
    } else {
        a.moveFront();
        b.moveFront();
        while (a.position() < (a.length() - 1)) {
            long valA = a.moveNext();
            long valB = b.moveNext();
            if (valA > valB) {
                return 1;
            } else if (valA < valB) {
                return -1;
            }
        }
    }
    return 0;
}

/*** Manipulation procedures ***/
void BigInteger::makeZero() {
    digits.moveFront();
    digits.clear();
    signum = 0;
}

void BigInteger::negate() {
    if (signum == 0) {
        return;
    } else {
        signum = -1 * signum;
    }
}

/*** BigInteger Arithmetic operations ***/
void negateList(List& L) {
    L.moveFront();
    while (L.position() < L.length()) {
        L.setBefore( -1*L.moveNext() );
    }
}

void sumList(List& S, List A, List B, int sgn) {
    A.moveBack();
    B.moveBack();
    S.clear();
    S.moveFront();
    if (B.length() > A.length()) {
        while (A.position() > 0) {
            ListElement a = A.movePrev();
            ListElement b = B.movePrev();
            S.insertAfter(a + (sgn * b));
        }
        while (B.position() > 0) {
            ListElement b = B.movePrev();
            S.insertAfter((sgn * b));
        }
    } else {
        while (B.position() > 0) {
            ListElement a = A.movePrev();
            ListElement b = B.movePrev();
            S.insertAfter(a + (sgn * b));
        }
        while (A.position() > 0) {
            ListElement a = A.movePrev();
            S.insertAfter(a);
        }
    }
}


int normalizeList(List& L) {
    if (L.front() < 0) {
        negateList(L);
        normalizeList(L);
        return -1;
    }
    L.moveBack();
    long carry = 0;
    while (L.position() > 1) {
        long num = L.movePrev() + carry;
        carry = 0;
        if (num >= base) {
            while (num >= base) {
                num = num - base;
                carry += 1;
            }
        } else if (num < 0 ) {
            while (num < 0) {
                num = num + base;
                carry -= 1;
            }
        }
        L.setAfter(num);
    }
    if (L.position() == 1) {
        long num = L.movePrev() + carry;
        L.setAfter(num);
        if (L.front() < 0) {
            negateList(L);
            normalizeList(L);
        }
    }

    L.moveFront();
    if (L.front() < 0) {
        return -1;
    } else if (L.front() > 0) {
        return 1;
    } else {
        return 0;
    }
}

void shiftList(List& L, int p) {
    L.moveBack();
    for (int i = 0; i < p; i += 1) {
        L.insertBefore(0);
    }
}

void scalarMultList(List& L, ListElement m) {
    L.moveBack();
    while (L.position() > 0) {
        L.setAfter(L.movePrev() * m);
    }
}

BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger C;
    List A = digits;
    List B = N.digits;
    if (signum == -1) {
        negateList(A);
    } 
    sumList(C.digits, A, B, N.signum);
    C.signum = normalizeList(C.digits);
    return C;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger C;
    List A = digits;
    List B = N.digits;
    if (signum == -1) {
        negateList(A);
    }
    sumList(C.digits, A, B, -N.signum);
    C.signum = normalizeList(C.digits);
    return C;
}

BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger C;
    int shift = 0;
    BigInteger A = *this;
    BigInteger B = N;
    long curr = 0;

    (B.digits).moveBack();
    while ((B.digits).position() > 0) {
        curr = (B.digits).movePrev();
        scalarMultList(A.digits, curr);
        normalizeList(A.digits);
        shiftList(A.digits, shift);
        shift += 1;
    }
    C.digits = A.digits;
    C.signum = A.signum;
    return C;
}

/*** Other Functions ***/
std::string BigInteger::to_string() {
    std::string s = "";
    List num = digits;
    num.moveFront();
    while (num.position() < num.length()) {
        s += std::to_string(num.moveNext())+" ";
    }
    return s;
}

/*** Overriden Operators ***/
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.BigInteger::to_string();
}

bool operator==( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) != 0) {
        return false;
    } else {
        return true;
    }
}

bool operator<( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) != -1) {
        return false;
    } else {
        return true;
    }
}

bool operator<=( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 1) {
        return false;
    } else {
        return true;
    }
}

bool operator>( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) != 1) {
        return false;
    } else {
        return true;
    }
}

bool operator>=( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == -1) {
        return false;
    } else {
        return true;
    }
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.add(B);
    return A;
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.sub(B);
    return A;
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A = A.mult(B);
    return A;
}









