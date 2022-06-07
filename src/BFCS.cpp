#include <climits>
#include "main.h"
#include "util.h"
#include <queue>
#include <iostream>

using namespace std;

// bellman-ford-moore with walk to the root strategy
// O(n^2m)

bool containsNegativeCycle(Graph& graph, int source){

    int n = graph.n;
    vector<number> distance(n, INFINITY);
    vector<bool> inQueue(n, false);
    vector<int> predecessor(n, -1);
    queue<int>Q;

    distance[source] = 0;
    Q.push(source);
    inQueue[source] = true;

    number c = 0;

    while (!Q.empty()){
        auto src = Q.front();
        Q.pop();
        inQueue[src] = false;
        for (auto neighbour: graph.neighbours[src]){
            if (distance[src] + neighbour.weight < distance[neighbour.dst]){
                c++;
                if (distance[source]<0 || isAncestor(predecessor, src, neighbour.dst, source)) {
                    cout<<c<<endl;
                    return true;
                }
                distance[neighbour.dst] = distance[src] + neighbour.weight;
                predecessor[neighbour.dst] = src;
                if (!inQueue[neighbour.dst]){
                    inQueue[neighbour.dst] = true;
                    Q.push(neighbour.dst);
                }
            }
        }
    }
    cout<<c<<endl;
    return false;
}
