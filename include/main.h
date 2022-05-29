#ifndef CODE_MAIN_H
#define CODE_MAIN_H

#define INFINITY INT_MAX/2

using namespace std;

#include <vector>

struct neighbour{
    int dst, weight;
    explicit neighbour(int dst=0, int weight=0): dst(dst), weight(weight){}
};

struct edge{
    int src, dst, weight;
    explicit edge(int src=0, int dst=0, int weight=0):src(src), dst(dst), weight(weight){}
};

struct Graph{
    vector<vector<neighbour>> neighbours;
    vector<edge> edges;
    int n;
    explicit Graph(int n): neighbours(n), n(n) {}
    void addEdge(int src, int dst, int weight){
        edges.emplace_back(src, dst, weight);
        neighbours[src].emplace_back(dst, weight);
    }
};

bool containsNegativeCycle(Graph &graph, int source);

#endif //CODE_MAIN_H
