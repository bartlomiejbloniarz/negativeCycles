#include <climits>
#include "main.h"
#include <unordered_set>
#include "util.h"

using namespace std;

// "A Faster Negative Cycle Detection Algorithm"
// O(n^2)

// strategy: time out and walk to the root

bool containsNegativeCycle(Graph &graph, int s){
    int n = graph.n;
    vector<int> d(n, INFINITY), pd(n, INFINITY), pi(n, -1), ns(n, 0);
    unordered_set<int> labeled_new, labeled_old;
    d[s] = 0;
    int source = s;
    int min_d_new, min_d_old, min_v_old, min_v_new;
    for (int i=1; i<=2*n; i++){
        ns[source]++;
        min_d_old = INFINITY;
        if (ns[source] > 2 || d[s] < 0)
            return true;
        for (auto neighbour: graph.neighbours[source]){
            int v = neighbour.dst, weight = neighbour.weight;
            pd[v] = d[v];
            if (d[v] > d[source] + weight){
                d[v] = d[source] + weight;
                pi[v] = source;
            }
            if (pd[v] > d[v]){
                labeled_new.insert(v);
                labeled_old.erase(v);
                min_d_new = d[v];
                min_v_new = v;
            }
            else
                min_d_new = INFINITY;
            if (min_d_new < min_d_old) {
                min_d_old = min_d_new;
                min_v_old = min_v_new;
            }
        }
        if (min_v_old == source){
            ns[source]--;
            i--;
        }
        for (auto v: labeled_old){
            if (min_d_old > d[v]) {
                min_d_old = d[v];
                min_v_old = v;
            }
        }
        source = min_v_old;
        for (auto v: labeled_new)
            labeled_old.insert(v);
        labeled_new.clear();
        if (labeled_old.empty())
            return false;
        labeled_old.erase(source);
    }
    return false;
}