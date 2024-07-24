#include "stack.h"
#include <vector>
#include <string>

template <typename T>
void Stack<T>::push(const T& item) {
    elements.push_back(item);
}

template <typename T>
void Stack<T>::pop() {
    if (!elements.empty()) {
        elements.pop_back();
    }
}

template <typename T>
T Stack<T>::top() const {
    if (!elements.empty()) {
        return elements.back();
    }
    return T(); // or throw an exception
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return elements.empty();
}

// Explicit template instantiation
template class Stack<int>;
template class Stack<double>;
template class Stack<std::string>;

// Specialization for pVERTEX
void Stack<pVERTEX>::push(pVERTEX item) {
    elements.push_back(item);
}

void Stack<pVERTEX>::pop() {
    if (!elements.empty()) {
        elements.pop_back();
    }
}

pVERTEX Stack<pVERTEX>::top() const {
    if (!elements.empty()) {
        return elements.back();
    }
    return nullptr; // or throw an exception
}

bool Stack<pVERTEX>::isEmpty() const {
    return elements.empty();
}