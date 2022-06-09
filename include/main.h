#ifndef CODE_MAIN_H
#define CODE_MAIN_H

#define INFINITY  1000000000000000000
#define number long long

using namespace std;

#include <vector>

struct neighbour{
    int dst;
    number weight;
    neighbour(int dst, number weight): dst(dst), weight(weight){}
};

struct edge{
    int src, dst;
    number weight;
    edge(int src, int dst, number weight):src(src), dst(dst), weight(weight){}
};

struct Graph{
    vector<vector<neighbour>> neighbours;
    vector<edge> edges;
    int n;
    explicit Graph(int n): neighbours(n), n(n) {}
    void addEdge(int src, int dst, number weight){
        edges.emplace_back(src, dst, weight);
        neighbours[src].emplace_back(dst, weight);
    }
};

bool containsNegativeCycle(Graph &graph, int source, number& labelingCount);

#endif //CODE_MAIN_H
