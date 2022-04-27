#include <climits>
#include "main.h"

using namespace std;

// O(nm)

// strategy: time out

bool containsNegativeCycle(Graph& graph, int source){
    int n = graph.n;
    vector<int> distance(n, INT_MAX);
    distance[source] = 0;
    for (int i=0; i<n-1; i++) {
        for (auto e: graph.edges) {
            if (distance[e.src] != INT_MAX && distance[e.dst] > distance[e.src] + e.weight) {
                distance[e.dst] = distance[e.src] + e.weight;
            }
        }
    }
    for (auto e: graph.edges) {
        if (distance[e.src] != INT_MAX && distance[e.dst] > distance[e.src] + e.weight) {
            return true;
        }
    }
    return false;
}

