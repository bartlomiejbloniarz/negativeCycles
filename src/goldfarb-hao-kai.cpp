#include <climits>
#include "main.h"
#include "util.h"
#include <queue>

using namespace std;

// level-based strategy
// O(nm)

bool containsNegativeCycle(Graph& graph, int source){

    int n = graph.n, k=1;
    vector<int> distance(n, INT_MAX);
    vector<int> predecessor(n, 0);
    vector<int> level(n, 0);
    vector<int> levelCount(n, 0);
    queue<int> Q1, Q2;

    distance[source] = 0;
    levelCount[1] = graph.neighbours[source].size();
    levelCount[0] = n - levelCount[1];
    for (auto neighbour: graph.neighbours[source]){
        distance[neighbour.dst] = neighbour.weight;
        predecessor[neighbour.dst] = source;
        level[neighbour.dst] = 1;
        Q1.push(neighbour.dst);
    }

    while(!(Q1.empty() && Q2.empty())){
        if (!Q1.empty()){
            auto src = Q1.front();
            Q1.pop();
            if (level[src] == k){
                for (auto neighbour: graph.neighbours[src]){
                    if (distance[src] != INT_MAX && distance[src] + neighbour.weight < distance[neighbour.dst]){
                        distance[neighbour.dst] = distance[src] + neighbour.weight;
                        predecessor[neighbour.dst] = src;
                        if (level[neighbour.dst] != k+1) {
                            levelCount[level[neighbour.dst]]--;
                            if (levelCount[level[neighbour.dst]] == 0)
                                return true;
                            Q2.push(neighbour.dst);
                            level[neighbour.dst] = k+1;
                            levelCount[k+1]++;
                        }
                    }
                }
            }
        }
        else{
            swap(Q1, Q2);
            k++;
        }
    }

    return false;
}
