#include <climits>
#include "main.h"
#include "util.h"
#include <stack>

using namespace std;

// bellman-ford-moore with amortized search strategy
// O(nm)

#define OUT_OF_STACKS  0
#define IN_NEW_PASS    1
#define IN_TOP_SORT    2
#define IN_PASS        3

bool containsNegativeCycle(Graph& graph, int source){

    int n = graph.n;
    counter amortizationCounter(n);
    vector<int> distance(n, INFINITY);
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
                            else if (status[neighbour.dst] == IN_TOP_SORT)
                                return true;
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
                int distNew = distance[src] + neighbour.weight;
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
