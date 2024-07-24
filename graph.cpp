/*
Name: Nived Reddy Ayyagari
ASU ID: 1226546986
File: graph.cpp
*/

#include "graph.h"
#include "heap.h"  
#include <iostream>
#include <iomanip>
#include <cfloat> 

using namespace std;

void GraphAlgorithms::PrintADJUSENT(const Graph& graph) {
    for (int i = 1; i <= graph.numVertices; ++i) {
        cout << "ADJ[" << i << "]:";
        pNODE current = graph.adjList[i];

        while (current != nullptr) {
            cout << "-->[" << current->u << " " << current->v << ": " << fixed << setprecision(2) << current->w << "]";
            current = current->next;
        }
        
        cout << endl;
    }
}


void GraphAlgorithms::Dijkstra(Graph& graph, int startVertex) {
    MinHeap minHeap(graph.numVertices);  // Ensure MinHeap is declared

    // Initialize vertices
    for (int i = 1; i <= graph.numVertices; ++i) {
        graph.V[i]->key = DBL_MAX;
        graph.V[i]->pi = -1;
        minHeap.insertElement(graph.V[i]);
    }

    graph.V[startVertex]->key = 0;
    minHeap.reduceKey(startVertex, 0);

    while (!minHeap.checkIfEmpty()) {
        pVERTEX u = minHeap.removeMin();
        pNODE current = graph.adjList[u->index];

        // Relaxation process
        while (current != nullptr) {
            int v = current->v;
            double weight = current->w;

            if (graph.V[v]->key > u->key + weight) {
                graph.V[v]->key = u->key + weight;
                graph.V[v]->pi = u->index;
                minHeap.reduceKey(graph.V[v]->position, graph.V[v]->key);
            }

            current = current->next;
        }
    }
}

void GraphAlgorithms::DijkstraPair(Graph& graph, int source, int destination) {
    // Run Dijkstra's algorithm from the source vertex
    Dijkstra(graph, source);

    // Check if the destination vertex is reachable
    if (graph.V[destination]->key == DBL_MAX) {
        graph.V[destination]->pi = -1;  // Marks as unreachable
    }
}