#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <vector>
#include <string>

enum COLOR { WHITE, GRAY, BLACK };

typedef struct TAG_VERTEX {
    int index;
    COLOR color;
    double key;
    int pi;
    int position;
} VERTEX;

typedef VERTEX *pVERTEX;

typedef struct TAG_NODE {
    int index;
    int u;
    int v;
    double w;
    struct TAG_NODE *next;
} NODE;

typedef NODE *pNODE;

struct Graph {
    int numVertices;
    std::vector<pNODE> adjList;
    pVERTEX *V;

    Graph(int n) : numVertices(n) {
        V = (pVERTEX *)calloc(n + 1, sizeof(pVERTEX));
        for (int i = 1; i <= n; ++i) {
            V[i] = (VERTEX *)calloc(1, sizeof(VERTEX));
            V[i]->index = i;
        }
        adjList.resize(n + 1, nullptr);
    }

    ~Graph() {
        for (int i = 1; i <= numVertices; ++i) {
            free(V[i]);
        }
        free(V);
    }
};

#endif 