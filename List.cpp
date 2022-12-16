/********************************************************************************* 
* Diwa Ashwini Vittala, dashwini
* 2022 Spring CSE101 PA6
* List.cpp
* List ADT 
**********************************************************************************/

#include <string>
#include <iostream>
#include <stdexcept>
#include <climits>
#include "List.h"

/*** Private Constructor ***/
// Node struct
List::Node::Node(ListElement x){
    data = x;
    next = prev = nullptr;
}


// Creates new List
List::List() {
    frontDummy = new Node(INT_MAX);
    backDummy = new Node(INT_MAX);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    pos_cursor = num_elements = 0;
}

// Copy list
List::List(const List& L){
    frontDummy = new Node(INT_MAX);
    backDummy = new Node(INT_MAX);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    pos_cursor = num_elements = 0;

    for (Node *N = L.frontDummy->next; N != L.backDummy; N = N->next) {
        insertBefore(N->data);
    }
    moveFront();
}

// Destroy list
List::~List(){
    while (num_elements > 0) {
        Node *N = frontDummy;
        frontDummy = N->next;
        num_elements--;
        delete N;
    }
    delete frontDummy;
    delete backDummy;
    pos_cursor = num_elements = 0;
}

/*** Access functions***/
// length(): Returns the length of this List.
int List::length() const {
    return(num_elements);
}

// front(): Returns the front element in this List. pre: length()>0
ListElement List::front() const {
    if (length() <= 0) {
        throw std::length_error("List: front(): List is not long enough to call front.\n");
    }
    return((frontDummy)->next->data);
}

// back(): Returns the back element in this List. pre: length()>0
ListElement List::back() const {
    if (length() <= 0) {
        throw std::length_error("List: back(): List is not long enough to call back.\n");
    }
    return((backDummy)->prev->data);
}

// position(): Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    if ((0 > pos_cursor) && (pos_cursor > length())) {
        throw std::range_error("List: position(): Position out of range.\n");
    }
    return(pos_cursor);
}

// peekNext(): Returns the element after the cursor. pre: position()<length()
ListElement List::peekNext() const {
    if (position() >= length()) {
        throw std::range_error("List: peekNext(): Position out of range.\n");
    }
    return(afterCursor->data);
}

// peekPrev(): Returns the element before the cursor. pre: position()>0
ListElement List::peekPrev() const {
    if (position() <= 0) {
        throw std::range_error("List: peekPrev(): Position out of range.\n");
    }
    return(beforeCursor->data);
}

/*** Manipulation procedures ***/
// clear(): Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    moveFront();
    while (length() != 0) {
        eraseAfter();
    }
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    pos_cursor = num_elements = 0;
}

// moveFront(): Moves cursor to position 0 in this List.
void List::moveFront() {
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

// moveBack(): Moves cursor to position length() in this List.
void List::moveBack() {
    pos_cursor = num_elements;
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
}

// moveNext(): Advances cursor to next higher position.
// Returns the List element that was passed over. pre: position()<length()
ListElement List::moveNext() {
    if (position() >= length()) {
        throw std::range_error("List: moveNext(): Position out of range.\n");
    }
    pos_cursor = pos_cursor + 1;
    beforeCursor = afterCursor;
    afterCursor = beforeCursor->next;
    return beforeCursor->data;
}

// movePrev(): Advances cursor to next lower position. Returns the List element that
// was passed over. pre: position()>0
ListElement List::movePrev() {
    if (position() <= 0) {
        throw std::range_error("List: movePrev(): Position out of range.\n");
    }
    pos_cursor = pos_cursor - 1;
    afterCursor = beforeCursor;
    beforeCursor = afterCursor->prev;
    return afterCursor->data;
}

// insertAfter(): Inserts x after cursor.
void List::insertAfter(ListElement x) {
    Node *N = new Node(x);
    beforeCursor->next = N;
    N->prev = beforeCursor;
    afterCursor->prev = N;
    N->next = afterCursor;
    afterCursor = N;
    num_elements = num_elements + 1;
}

// insertBefore(): Inserts x before cursor.
void List::insertBefore(ListElement x) {
    insertAfter(x);
    moveNext();
}

// setAfter(): Overwrites the List element after the cursor with x. pre: position()<length()
void List::setAfter(ListElement x) {
    if (position() >= length()) {
        throw std::range_error("List: setAfter(): Position out of range.\n");
    }
    afterCursor->data = x;
}

// setBefore(): Overwrites the List element before the cursor with x. pre: position()>0
void List::setBefore(ListElement x) {
    if (position() <= 0) {
        throw std::range_error("List: setBefore(): Position out of range.\n");
    }
    beforeCursor->data = x;
}

// eraseAfter(): Deletes element after cursor. pre: position()<length()
void List::eraseAfter() {
    if (position() >= length()) {
        throw std::range_error("List: eraseAfter(): Position out of range.\n");
    }
    Node *N = afterCursor->next;
    beforeCursor->next = N;
    N->prev = beforeCursor;
    delete afterCursor;
    afterCursor = N;
    num_elements = num_elements - 1;
}

// eraseBefore(): Deletes element before cursor. pre: position()>0
void List::eraseBefore() {
    if (position() <= 0) {
        throw std::range_error("List: eraseBefore(): Position out of range.\n");
    }
    Node *N = beforeCursor->prev;
    afterCursor->prev = N;
    N->next = afterCursor;
    delete beforeCursor;
    beforeCursor = N;
    pos_cursor = pos_cursor - 1;
    num_elements = num_elements - 1;
}


/*** Other Functions ***/
// findNext(): finds next instance of x after cursor, returns -1 if not found
int List::findNext(ListElement x) {
    while (position() < length()) {
        if (afterCursor->data == x) {
            moveNext();
            return position();
        } else {
            moveNext();
        }
    }
    pos_cursor = length();
    return -1;
}

// findPrev(): finds previous instance of x, returns -1 if not found
int List::findPrev(ListElement x) {
    while (position() > 0) {
        if (beforeCursor->data == x) {
            movePrev(); 
            return position();
        } else {
            movePrev();
        }
    }
    pos_cursor = 0;
    return -1;
}

// cleanup(): Removes any repeated elements in this List
void List::cleanup() {
    List dup; 
    int pos = pos_cursor;
    Node *oldAfter = afterCursor;
    Node *oldBefore = beforeCursor;
    moveFront(); 
    while (pos_cursor < length()) {
        ListElement cursorData = moveNext();
        dup.moveFront();
        if (dup.findNext(cursorData) == -1) {
            dup.insertAfter(cursorData);
        } else {
            if (pos_cursor <= pos) {
                pos = pos - 1;
            }
            if (beforeCursor == oldAfter) {
                oldAfter = beforeCursor->next;
            } 
            if (beforeCursor == oldBefore) {
                oldBefore = beforeCursor->prev;
            }
            eraseBefore();
        }
    }
    pos_cursor = pos;
    afterCursor = oldAfter;
    beforeCursor = oldBefore;
    return;
}

// concat(): Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
    List C = *this;
    C.moveBack();
    for (Node *N = L.frontDummy->next; N != L.backDummy; N = N->next) {
        C.insertBefore(N->data);
    }
    C.moveFront();
    return C;
}

// to_string(): Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    std::string s = "";
    for(Node *N = frontDummy; N != backDummy; N = N->next){
        s += std::to_string(N->data)+" ";
    }
    return s;
}

// equals(): Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
    if (length() != R.length()) {
        return false; 
    }
    Node *N = frontDummy->next; // first element in a
    Node *M = (R.frontDummy)->next; // first element in r
    while(N != backDummy) {
        if (N->data != M->data) {
            return false;
        }
        N = N->next;
        M = M->next;
    }
    return true;
}

// /*** Overriden Operators ***/
// operator<<(): Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
    return stream << L.List::to_string();
}

// operator==(): Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==(const List& A, const List& B ) {
    return A.List::equals(B);
}

// operator=(): Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
    if(this != &L){ // not self assignment
        List temp = L;
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
     }
     return *this;
}



