#include "heap.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cfloat>

using namespace std;

MinHeap::MinHeap(int capacity) {
    heap = (pHEAP)malloc(sizeof(HEAP));
    heap->capacity = capacity;
    heap->size = 0;
    heap->H = (pELEMENT *)malloc((capacity + 1) * sizeof(pELEMENT));
}

MinHeap::~MinHeap() {
    free(heap->H);
    free(heap);
}

void MinHeap::insertElement(pELEMENT element) {
    if (heap->size >= heap->capacity) {
        throw overflow_error("Heap is full");
    }
    heap->size++;
    int index = heap->size;
    heap->H[index] = element;
    heap->H[index]->position = index;
    moveUp(index);
}

pELEMENT MinHeap::removeMin() {
    if (heap->size == 0) {
        throw underflow_error("Heap is empty");
    }
    pELEMENT minElement = heap->H[1];
    heap->H[1] = heap->H[heap->size];
    heap->H[1]->position = 1;
    heap->size--;
    moveDown(1);
    return minElement;
}

// Peeks at the minimum element in the heap without removing it
pELEMENT MinHeap::peekMin() const {
    if (heap->size == 0) {
        throw underflow_error("Heap is empty");
    }
    return heap->H[1];
}

// Checks if the heap is empty
bool MinHeap::checkIfEmpty() const {
    return heap->size == 0;
}

// Reduces the key of an element at a given index and maintains heap property
void MinHeap::reduceKey(int index, double newKey) {
    if (newKey > heap->H[index]->key) {
        throw invalid_argument("New key is greater than current key");
    }
    heap->H[index]->key = newKey;
    moveUp(index);
}

// Gets the current size of the heap
int MinHeap::getHeapSize() const {
    return heap->size;
}

// Moves an element up the heap to maintain heap property
void MinHeap::moveUp(int index) {
    while (index > 1 && heap->H[index]->key < heap->H[index / 2]->key) {
        exchangeElements(index, index / 2);
        index = index / 2;
    }
}

// Moves an element down the heap to maintain heap property
void MinHeap::moveDown(int index) {
    int smallest = index;
    int left = 2 * index;
    int right = 2 * index + 1;

    if (left <= heap->size && heap->H[left]->key < heap->H[smallest]->key) {
        smallest = left;
    }
    if (right <= heap->size && heap->H[right]->key < heap->H[smallest]->key) {
        smallest = right;
    }
    if (smallest != index) {
        exchangeElements(index, smallest);
        moveDown(smallest);
    }
}

// Exchanges elements at two indices in the heap
void MinHeap::exchangeElements(int i, int j) {
    pELEMENT temp = heap->H[i];
    heap->H[i] = heap->H[j];
    heap->H[i]->position = i;
    heap->H[j] = temp;
    heap->H[j]->position = j;
}