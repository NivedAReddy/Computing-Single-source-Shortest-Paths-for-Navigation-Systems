#ifndef HEAP_H
#define HEAP_H

#include "data_structures.h"

typedef VERTEX ELEMENT;
typedef ELEMENT *pELEMENT;

typedef struct TAG_HEAP {
    int capacity;
    int size;
    pELEMENT *H;
} HEAP;

typedef HEAP *pHEAP;

class MinHeap {
public:
    MinHeap(int capacity);
    ~MinHeap();
    void insertElement(pELEMENT element);
    pELEMENT removeMin();
    pELEMENT peekMin() const;
    bool checkIfEmpty() const;
    void reduceKey(int index, double newKey);
    int getHeapSize() const;

private:
    pHEAP heap;
    void moveUp(int index);
    void moveDown(int index);
    void exchangeElements(int i, int j);
};

#endif // HEAP_H