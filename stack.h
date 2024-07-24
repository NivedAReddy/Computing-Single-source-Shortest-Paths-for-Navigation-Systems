#ifndef STACK_H
#define STACK_H

#include <vector>
#include "data_structures.h"

using namespace std;

template <typename T>
class Stack {
public:
    void push(const T& item);
    void pop();
    T top() const;
    bool isEmpty() const;

private:
    vector<T> elements;
};

template <>
class Stack<pVERTEX> {
public:
    void push(pVERTEX item);
    void pop();
    pVERTEX top() const;
    bool isEmpty() const;

private:
    vector<pVERTEX> elements;
};

#endif // STACK_H
