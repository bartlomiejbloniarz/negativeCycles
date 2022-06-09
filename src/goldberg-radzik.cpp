#include <climits>
#include "main.h"
#include "util.h"
#include <stack>

using namespace std;

// goldberg-radzik with admissible search strategy
// O(nm)

#define OUT_OF_STACKS  0
#define IN_NEW_PASS    1
#define IN_TOP_SORT    2
#define IN_PASS        3

bool containsNegativeCycle(Graph& graph, int source, number& labelingCount){

    int n = graph.n;
    counter amortizationCounter(n);
    vector<number> distance(n, INFINITY);
    vector<int> status(n, OUT_OF_STACKS);
    vector<int> parent(n);
    vector<int> current(n);
    stack<int> newPass, pass, topSort, sccPass;

    newPass.push(source);
    status[source] = IN_NEW_PASS;
    parent[source] = source;
    distance[source] = 0;

    // main loop
    while(!newPass.empty()){

        vector<vector<int>> invertedNeighbours(n);
        vector<bool> visited(n, false);
        //dfs
        int src = source;
        visited[src] = true;
        while(true){
            int i, size = graph.neighbours[src].size();
            for(i=current[src]; i<size; i++){
                auto neighbour = graph.neighbours[src][i];
                if (distance[src] + neighbour.weight <= distance[neighbour.dst]){
                    invertedNeighbours[neighbour.dst].push_back(src);
                    if (!visited[neighbour.dst]) {
                        current[src] = i + 1;
                        topSort.push(src);
                        visited[neighbour.dst] = true;
                        current[neighbour.dst] = 0;
                        src = neighbour.dst;
                        break;
                    }
                }
            }
            if (i == size){
                sccPass.push(src);
                if (!topSort.empty()){
                    src = topSort.top();
                    topSort.pop();
                }
                else
                    break;
            }
        }

        // calculate scc
        vector<int>scc(n, -1);
        int currentScc=0;
        while(!sccPass.empty()){
            int v = sccPass.top();
            sccPass.pop();
            if (scc[v] == -1){
                currentScc++;
                topSort.push(v);
                while(!topSort.empty()){
                    v = topSort.top();
                    topSort.pop();
                    scc[v] = currentScc;
                    for (auto w: invertedNeighbours[v]){
                        if (scc[w] == -1){
                            topSort.push(w);
                        }
                    }
                }
            }
        }

        //check for cycles
        for (auto e: graph.edges){
            if (distance[e.src] != INFINITY && distance[e.src] + e.weight < distance[e.dst] && scc[e.src] == scc[e.dst] && scc[e.src]!=-1)
                return true;
        }

        // topological sorting
        while(!newPass.empty()) {

            src = newPass.top();
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
                while(true){
                    int i, size = graph.neighbours[src].size();
                    for(i=current[src]; i<size; i++){
                        auto neighbour = graph.neighbours[src][i];
                        if (distance[src] + neighbour.weight <= distance[neighbour.dst]){
                            if (status[neighbour.dst] < IN_TOP_SORT) {
                                current[src] = i + 1;
                                topSort.push(src);
                                status[neighbour.dst] = IN_TOP_SORT;
                                current[neighbour.dst] = 0;
                                src = neighbour.dst;
                                break;
                            }
                        }
                    }
                    if (i == size){
                        status[src] = IN_PASS;
                        pass.push(src);
                        if (!topSort.empty()){
                            src = topSort.top();
                            topSort.pop();
                        }
                        else
                            break;
                    }
                }
            }
        }

        // bellman-ford pass
        while(!pass.empty()){
            auto src = pass.top();
            pass.pop();
            status[src] = OUT_OF_STACKS;

            for (auto neighbour: graph.neighbours[src]){
                number distNew = distance[src] + neighbour.weight;
                if (distNew < distance[neighbour.dst]){
                    labelingCount++;
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