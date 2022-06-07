#include <climits>
#include "main.h"
#include <stack>

using namespace std;

// bellman-ford-moore with amortized search strategy
// O(nm)

#define OUT_OF_STACKS  0
#define IN_NEW_PASS    1
#define IN_TOP_SORT    2
#define IN_PASS        3

void strongConnect(int v, vector<int> &indexes, vector<int> &lowLink, stack<int> &S, vector<bool> &onStack, int &index, Graph& graph, vector<number> &distance, vector<int> &scc, stack<int> &pass, vector<int> &status){
    indexes[v] = index;
    lowLink[v] = index;
    index++;
    S.push(v);
    onStack[v] = true;

    for(auto neighbour: graph.neighbours[v]) {
        int w = neighbour.dst;
        if (distance[v] + neighbour.weight <= distance[w]) {
            if (indexes[w] == -1){
                strongConnect(w, indexes, lowLink, S, onStack, index, graph, distance, scc, pass, status);
                lowLink[v] = min(lowLink[v], lowLink[w]);
            }
            else if (onStack[w]){
                lowLink[v] = min(lowLink[v], indexes[w]);
            }
        }
    }

    if (lowLink[v] == indexes[v]){
        int w;
        do{
            w = S.top();
            S.pop();
            onStack[w] = false;
            scc[w] = indexes[v];
            pass.push(w);
            status[w] = IN_PASS;
        } while (w != v);
    }

}

bool containsNegativeCycle(Graph& graph, int source){

    int n = graph.n;
    vector<number> distance(n, INFINITY);
    vector<int> status(n, OUT_OF_STACKS);
    vector<int> parent(n);
    vector<int> current(n);
    stack<int> newPass, pass, topSort;

    newPass.push(source);
    status[source] = IN_NEW_PASS;
    parent[source] = source;
    distance[source] = 0;

    // main loop
    while(!newPass.empty()){

        int index = 0;
        vector<int> indexes(n, -1), lowLink(n);
        stack<int> S;
        vector<bool> onStack(n, false);
        vector<int> scc(n, -1);

        // topological sorting
        while(!newPass.empty()) {

            auto src = newPass.top();
            newPass.pop();

            if (status[src] == IN_NEW_PASS) {

                //looking for any edge with negative reduced cost outgoing from src if any - start dfs
                int dst = -1;
                for (auto neighbour: graph.neighbours[src]) {
                    if (distance[src] + neighbour.weight < distance[neighbour.dst]) {
                        dst = neighbour.dst;
                        break;
                    }
                }
                if (dst != -1) {
                    status[src] = IN_TOP_SORT;
                    current[src] = 0;
                } else
                    status[src] = OUT_OF_STACKS;
            }

            if (status[src] == IN_TOP_SORT){

                //dfs
                strongConnect(src, indexes, lowLink, S, onStack, index, graph, distance, scc, pass, status);

            }
        }

        //check for cycles
        for (auto e: graph.edges){
            if (distance[e.src] != INFINITY && distance[e.src] + e.weight < distance[e.dst] && scc[e.src] == scc[e.dst])
                return true;
        }

        // bellman-ford pass
        while(!pass.empty()){
            auto src = pass.top();
            pass.pop();
            status[src] = OUT_OF_STACKS;

            for (auto neighbour: graph.neighbours[src]){
                number distNew = distance[src] + neighbour.weight;
                if (distNew < distance[neighbour.dst]){
                    distance[neighbour.dst] = distNew;
                    parent[neighbour.dst] = src;
                    if (status[neighbour.dst] == OUT_OF_STACKS){
                        newPass.push(neighbour.dst);
                        status[neighbour.dst] = IN_NEW_PASS;
                    }
                }
            }
        }
    }
    return false;
}
