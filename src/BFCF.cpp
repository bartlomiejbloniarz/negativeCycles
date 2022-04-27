#include <climits>
#include "main.h"
#include "util.h"
#include <queue>

using namespace std;

// bellman-ford-moore with amortized search strategy
// O(nm)


bool containsNegativeCycle(Graph& graph, int source){

    int n = graph.n;
    counter amortizationCounter(n);
    vector<int> distance(n, INT_MAX);
    vector<bool> inQueue(n, false);
    vector<int> predecessor(n);
    queue<int>Q;

    distance[source] = 0;
    Q.push(source);
    inQueue[source] = true;

    while (!Q.empty()){
        auto src = Q.front();
        Q.pop();
        inQueue[src] = false;
        for (auto neighbour: graph.neighbours[src]){
            amortizationCounter.increment();
            if (distance[src] != INT_MAX && distance[src] + neighbour.weight < distance[neighbour.dst]){
                if (amortizationCounter.isActive() && isAncestor(predecessor, src, neighbour.dst, source))
                    return true;
                distance[neighbour.dst] = distance[src] + neighbour.weight;
                predecessor[neighbour.dst] = src;
                if (!inQueue[neighbour.dst]){
                    inQueue[neighbour.dst] = true;
                    Q.push(neighbour.dst);
                }
            }
        }
    }
    return false;
}
