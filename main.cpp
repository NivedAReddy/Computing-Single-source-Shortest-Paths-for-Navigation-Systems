#include "main.h"
#include "util.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cfloat>
#include <stack>
#include <iomanip>

using namespace std;

void loadGraphFromFile(const string& filename, Graph& graph, int flag, bool isDirected) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        exit(EXIT_FAILURE);
    }
    int n, m;
    file >> n >> m;

    auto addNode = [&](int edgeIndex, int u, int v, double w) {
        pNODE newNode = (pNODE)calloc(1, sizeof(NODE));
        newNode->index = edgeIndex;
        newNode->u = u;
        newNode->v = v;
        newNode->w = w;
        if (flag == 1) {
            newNode->next = graph.adjList[u];
            graph.adjList[u] = newNode;
        }
        else if (flag == 2) {
            if (graph.adjList[u] == nullptr) {
                graph.adjList[u] = newNode;
            }
            else {
                pNODE current = graph.adjList[u];
                while (current->next) {
                    current = current->next;
                }
                current->next = newNode;
            }
        }
    };

    for (int i = 0; i < m; ++i) {
        int edgeIndex, u, v;
        double w;
        file >> edgeIndex >> u >> v >> w;

        if (isDirected) {
            addNode(edgeIndex, u, v, w);
        } 
        else {
            addNode(edgeIndex, u, v, w);
            addNode(edgeIndex, v, u, w);
        }
    }
    file.close();
}

void printPath(Graph& graph, int source, int destination) {
    stack<pVERTEX> pathStack;
    int current = destination;

    while (current != -1) {
        pathStack.push(graph.V[current]);
        current = graph.V[current]->pi;
    }

    cout << "The shortest path from " << source << " to " << destination << " is:" << endl;

    while (!pathStack.empty()) {
        pVERTEX vertex = pathStack.top();
        pathStack.pop();
        cout << "[" << vertex->index << ":" << setw(8) << fixed << setprecision(2) << vertex->key << "]";
        if (!pathStack.empty()) {
            cout << "-->";
        }
    }
    cout << "." << endl;
}

void printUsageAndExit() {
    cerr << "Usage: ./PJ3 <InputFile> <GraphType> <Flag>\n";
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printUsageAndExit();
    }

    string filename = argv[1];
    string graphType = argv[2];
    int flag = stoi(argv[3]);

    if (graphType != "DirectedGraph" && graphType != "UndirectedGraph") {
        printUsageAndExit();
    }

    if (flag != 1 && flag != 2) {
        printUsageAndExit();
    }

    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return 1;
    }

    int numVertices, numEdges;
    infile >> numVertices >> numEdges;
    infile.close();

    Graph graph(numVertices);
    bool isDirected = (graphType == "DirectedGraph");
    loadGraphFromFile(filename, graph, flag, isDirected);

    string command;
    int lastSource = -1, lastDestination = -1;

    while (cin >> command) {
        command = Util::toUpper(command);
        if (command == "STOP") {
            break;
        }
        else if (command == "PRINTADJ") {
            GraphAlgorithms::PrintADJUSENT(graph);
        }
        else if (command == "SINGLEPAIR") {
            int source, destination;
            cin >> source >> destination;
            GraphAlgorithms::DijkstraPair(graph, source, destination);
            lastSource = source;
            lastDestination = destination;
        }
        else if (command == "SINGLESOURCE") {
            int source;
            cin >> source;
            GraphAlgorithms::Dijkstra(graph, source); 
            lastSource = source;
            lastDestination = -1;
        }
        else if (command == "PRINTLENGTH") {
            int s, t;
            cin >> s >> t;
            
            if (s == lastSource && (lastDestination == -1 || t == lastDestination)) {
                if (graph.V[t]->key == DBL_MAX) {
                    cout << "There is no path from " << s << " to " << t << ".\n";
                }
                else {
                    cout << "The length of the shortest path from " << s << " to " << t << " is:     "
                         << fixed << setprecision(2) << graph.V[t]->key << "\n";
                }
            }
            else {
                cerr << "Invalid instruction.\n";
            }
        }
        else if (command == "PRINTPATH") {
            int s, t;
            cin >> s >> t;
            if (s == lastSource && (lastDestination == -1 || t == lastDestination)) {
                if (graph.V[t]->key == DBL_MAX) {
                    cout << "There is no path from " << s << " to " << t << ".\n";
                }
                else {
                    printPath(graph, s, t); 
                }

            }
            else {
                cerr << "Invalid instruction.\n";
            }
        }
        else {
            cerr << "Invalid instruction.\n"; 
        }
    }

    return 0;
}