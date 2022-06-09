#include <climits>
#include "main.h"
#include "util.h"
#include <stack>
#include <queue>

using namespace std;

// goldberg-radzik with admissible graph search strategy
// O(nm)

#define OUT_OF_STACKS  0
#define IN_NEW_PASS    1
#define IN_TOP_SORT    2

//static void scan(int src, Graph &graph, stack<int>&topSort, vector<int> &status, vector<number>& distance, number &labelingCount){
//    for (auto neighbour: graph.neighbours[src]){
//        if (distance[src] + neighbour.weight < distance[neighbour.dst]){
//            distance[neighbour.dst] = distance[src] + neighbour.weight;
//            parent[neighbour.dst] = src;
//            if (status[neighbour.dst] != IN_TOP_SORT){
//                topSort.push(neighbour.dst);
//                status[neighbour.dst] = IN_NEW_PASS;
//            }
//        }
//    }
//}

bool containsNegativeCycle(Graph& graph, int source, number& labelingCount) {

    int n = graph.n;
    vector<number> distance(n, INFINITY);
    vector<int> status(n, OUT_OF_STACKS);
    vector<int> parent(n);
    vector<int> current(n, 0);
    stack<int> newPass, topSort, sccPass, topSort1;

    topSort.push(source);
    status[source] = IN_NEW_PASS;
    parent[source] = source;
    distance[source] = 0;

    queue<int> bfsQueue;
    bfsQueue.push(source);
    vector<int> visited(n, false);
    vector<int> reachable;
    vector<edge> edges;

    while (!bfsQueue.empty()){
        int v = bfsQueue.front();
        bfsQueue.pop();
        visited[v] = true;
        reachable.emplace_back(v);
        for (auto neighbour: graph.neighbours[v]){
            edges.emplace_back(v, neighbour.dst, neighbour.weight);
            if (!visited[neighbour.dst]){
                bfsQueue.push(neighbour.dst);
            }
        }
    }

    // main loop
    while (!topSort.empty()) {

        vector<vector<int>> invertedNeighbours(n);
        visited.assign(n, false);
        //dfs
        for (int src: reachable) {
            if (visited[src]){
                continue;
            }
            visited[src] = true;
            current[src] = 0;
            while (true) {
                int i, size = graph.neighbours[src].size();
                for (i = current[src]; i < size; i++) {
                    auto neighbour = graph.neighbours[src][i];
                    if (distance[src] + neighbour.weight <= distance[neighbour.dst]) {
                        invertedNeighbours[neighbour.dst].push_back(src);
                        if (!visited[neighbour.dst]) {
                            current[src] = i + 1;
                            topSort1.push(src);
                            visited[neighbour.dst] = true;
                            current[neighbour.dst] = 0;
                            src = neighbour.dst;
                            break;
                        }
                    }
                }
                if (i == size) {
                    sccPass.push(src);
                    if (!topSort1.empty()) {
                        src = topSort1.top();
                        topSort1.pop();
                    } else
                        break;
                }
            }
        }

        // calculate scc
        vector<int> scc(n, -1);
        int currentScc = 0;
        while (!sccPass.empty()) {
            int v = sccPass.top();
            sccPass.pop();
            if (scc[v] == -1) {
                currentScc++;
                topSort1.push(v);
                while (!topSort1.empty()) {
                    v = topSort1.top();
                    topSort1.pop();
                    scc[v] = currentScc;
                    for (auto w: invertedNeighbours[v]) {
                        if (scc[w] == -1) {
                            topSort1.push(w);
                        }
                    }
                }
            }
        }

        //check for cycles
        for (auto e: edges) {
            if (distance[e.src] + e.weight < distance[e.dst] &&
                scc[e.src] == scc[e.dst] && scc[e.src] != -1)
                return true;
        }


        while (!topSort.empty()) {
            int src = topSort.top();
            topSort.pop();
            if (status[src] == IN_TOP_SORT) {
                newPass.push(src);
            } else if (status[src] == IN_NEW_PASS) {
                topSort.push(src);
                status[src] = IN_TOP_SORT;
                for (auto neighbour: graph.neighbours[src]) {
                    labelingCount++;
                    if (distance[src] + neighbour.weight < distance[neighbour.dst]) {
                        distance[neighbour.dst] = distance[src] + neighbour.weight;
                        parent[neighbour.dst] = src;
                        if (status[neighbour.dst] != IN_TOP_SORT) {
                            topSort.push(neighbour.dst);
                            status[neighbour.dst] = IN_NEW_PASS;
                        }
                    }
                }
            }
        }
        while (!newPass.empty()) {
            int src = newPass.top();
            newPass.pop();
            for (auto neighbour: graph.neighbours[src]) {
                labelingCount++;
                if (distance[src] + neighbour.weight < distance[neighbour.dst]) {
                    distance[neighbour.dst] = distance[src] + neighbour.weight;
                    parent[neighbour.dst] = src;
                    if (status[neighbour.dst] != IN_TOP_SORT) {
                        topSort.push(neighbour.dst);
                        status[neighbour.dst] = IN_NEW_PASS;
                    }
                }
            }
            status[src] = OUT_OF_STACKS;
        }
    }

    return false;
}