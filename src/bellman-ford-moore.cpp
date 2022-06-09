#include <climits>
#include "main.h"
#include <queue>

using namespace std;

// Shortest Path Faster Algorithm (SPFA)
// O(nm)

void bellman_ford_moore(Graph& graph, int source, number& labelingCount){

    int n = graph.n;
    vector<number> distance(n, INFINITY);
    vector<bool> inQueue(n, false);
    queue<int>Q;

    distance[source] = 0;
    Q.push(source);
    inQueue[source] = true;

    while (!Q.empty()){
        auto src = Q.front();
        Q.pop();
        inQueue[src] = false;
        for (auto neighbour: graph.neighbours[src]){
            labelingCount++;
            if (distance[src] + neighbour.weight < distance[neighbour.dst]){
                distance[neighbour.dst] = distance[src] + neighbour.weight;
                if (!inQueue[neighbour.dst]){
                    inQueue[neighbour.dst] = true;
                    Q.push(neighbour.dst);
                }
            }
        }
    }
}

