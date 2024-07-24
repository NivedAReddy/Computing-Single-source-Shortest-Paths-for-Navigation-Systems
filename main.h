#ifndef MAIN_H
#define MAIN_H

#include "data_structures.h"
#include "heap.h"
#include "stack.h"
#include "graph.h"
#include "util.h"

// Function declaration
void loadGraphFromFile(const std::string& filename, Graph& graph, int flag, bool isDirected);

#endif // MAIN_H