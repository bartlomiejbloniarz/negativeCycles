#include <climits>
#include "main.h"
#include <unordered_set>
#include "util.h"
#include <iostream>
using namespace std;

// "A Faster Negative Cycle Detection Algorithm"
// O(n^2)

// strategy: time out and walk to the root

bool containsNegativeCycle(Graph &graph, int s){
    int n = graph.n;
    vector<number> d(n, INFINITY), pd(n, INFINITY);
    vector<int> pi(n, -1), ns(n, 0);
    Set labeled_new(n), labeled_old(n);
    d[s] = 0;
    int source = s;
    number min_d_new, min_d_old;
    int min_v_old, min_v_new;
    for (int i=1; i<=2*n; i++){
        cout<<source<<endl;
        ns[source]++;
        min_d_old = INFINITY;
        if (ns[source] > 2 || d[s] < 0)
            return true;
        for (auto neighbour: graph.neighbours[source]){
            int v = neighbour.dst;
            number weight = neighbour.weight;
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
                min_d_old = d[v];
                min_v_old = v;
            }
        }
        if (min_v_old == source){
            cout<<"decreasing"<<endl;
            ns[source]--;
            i--;
        }
        for (LinkedListNode* node = labeled_old.list.head->next; node != labeled_old.list.tail; node = node->next){
            int v = node->x;
            if (min_d_old > d[v]) {
                min_d_old = d[v];
                min_v_old = v;
            }
        }
        source = min_v_old;
        for (LinkedListNode* node = labeled_new.list.head->next; node != labeled_new.list.tail; node = node->next)
            labeled_old.insert(node->x);
        labeled_new.clear();
        if (labeled_old.isEmpty())
            return false;
        labeled_old.erase(source);
    }
    return false;
}