/********************************************************************************* 
* Diwa Ashwini Vittala, dashwini
* 2022 Spring CSE101 PA6
* ListTest.cpp
* Program to test List ADT
**********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;


void print(List &L) {
    L.moveFront();
    while (L.position() < L.length()) {
        cout << "\nposition: " << L.position();
        cout << " - data: " << L.peekNext();
        L.moveNext();
    }
}

int main(){
    // insert tests
    List A, B;
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(4);
    cout << "\nAdded 1,2,4 to A and length is: " << A.length();

    A.insertAfter(3);
    A.insertAfter(4);
    A.insertAfter(4);
    cout << "\nAdded 3,4,4 to A so now Length is: " << A.length();
    cout << "\n\nPRINTING LIST A";
    print(A);

    A.moveBack();
    A.insertBefore(1);
    A.insertBefore(4);
    cout << "\nAdded 1,4 to A so now Length is: " << A.length();

    A.moveBack();
    while (A.position() > 0) {
        if (A.findPrev(4) == -1) {
            break;
        }
        A.setAfter(1);
        A.setBefore(2);
    }
    cout << "\nChanged all the 4s to 1s, and the number before it to 2";
    print(A);

    A.moveFront();
    A.moveNext();
    A.eraseBefore();
    A.eraseAfter();
    cout << "\nErase first two elements";
    print(A);

    A.moveFront();
    while (A.position() < A.length()) {
        if (A.findNext(1) == -1) {
            break;
        }
        A.setBefore(9);
    }
    cout << "\nFind all the 1s and set the element before it to 9.";
    print(A);

    cout << "\n\nPlease input values for a list of length 5:\n";
    int val = 0;
    for (int i = 0; i < 5; i += 1) {
        cin >> val;
        B.insertBefore(val);
    }
    cout << "\n\nPrinting the list you just input:";
    print(B);

    cout << "\n\nWhat do you want to do with it?";
    cout << "\n1 = find a value in the list";
    cout << "\n2 = remove repeats\n3 = set a value\n";
    cout << "4 = concat with A\n";
    cout << "OPTION: ";
    cin >> val;

    if (val == 1) {
        int num = 0;
        cout << "\nWhat do you want to find? ";
        cin >> num;
        B.moveFront();
        if (B.findNext(num) == -1) {
            cout << "\nNumber was not in list.\n";
        } else {
            cout << "\nNumber was in the list, position = " << (B.position() - 1);
        }
    } else if (val == 2) {
        cout << "\nRemoving repeats...";
        cout << "\n\nPrinting list without repeats:";
        B.cleanup();
        print(B);
    } else if (val == 3) {
        int num = 0;
        cout << "\nWhat do you want to replace? VALUE:";
        cin >> num;
        cout << "\nWhat do you want to replace it with? NEW VALUE:";
        cin >> val;
        B.moveFront();
        if (B.findNext(num) == -1) {
            cout << "\nNumber was not in list.\n";
        } else {
            B.eraseBefore();
            B.insertBefore(val);
            B.moveFront();
            print(B);
        }
    } else if (val == 4) {
        List C = B.concat(A);
        print(C);
    } else {
        cout << "\n\n...ENDING PROGRAM...";
    }
    cout << "\n~~~~~~~~~\n";
    return 0;
}
