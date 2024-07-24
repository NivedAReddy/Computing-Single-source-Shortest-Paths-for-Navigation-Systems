#ifndef GRAPH_H
#define GRAPH_H

#include "data_structures.h"

class GraphAlgorithms {
public:
    static void bfs(const Graph& graph, int startVertex);
    static void dfs(const Graph& graph, int startVertex);
    static void PrintADJUSENT(const Graph& graph);
    static void Dijkstra(Graph& graph, int startVertex);
    static void DijkstraPair(Graph& graph, int source, int destination);
};

#endif // GRAPH_H