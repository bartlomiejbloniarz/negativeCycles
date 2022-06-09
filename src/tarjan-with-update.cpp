#include <climits>
#include "main.h"
#include "util.h"

#define epsilon 1

using namespace std;

// tarjan with subtree disassembly and update
// O(nm)


bool disassemble(int x, LinkedList* children, Queue &Q, int v, number delta, vector<number> &distance){
    for (LinkedListNode* node = children[x].head->next; node != children[x].tail; ){
        int y = node->x;
        if (y == v)
            return true;
        else{
            auto temp = node->next;
            node->unlink();
            node->x = -1;
            Q.remove(y);
            distance[y] = distance[y] - delta + epsilon;
            if (disassemble(y, children, Q, v, delta, distance))
                return true;
            node = temp;
        }
    }
    return false;
}


bool containsNegativeCycle(Graph& graph, int source, number& labelingCount){

    int n = graph.n;
    vector<number> distance(n, INFINITY);
    LinkedList children[n];
    Queue Q(n);
    vector<int> parent(n);
    LinkedListNode childrenNodes[n];
    distance[source] = 0;
    Q.push(source);

    while (!Q.isEmpty()){
        int src = Q.pop();
        for (auto neighbour: graph.neighbours[src]){
            number delta = distance[neighbour.dst] - distance[src] - neighbour.weight;
            labelingCount++;
            if (delta > 0){
                if (neighbour.dst == source) {
                    return true;
                }
                distance[neighbour.dst] -= delta;
                if (childrenNodes[neighbour.dst].x != -1) {
                    childrenNodes[neighbour.dst].unlink();
                    childrenNodes[neighbour.dst].x = -1;
                }
                parent[neighbour.dst] = src;
                Q.push(neighbour.dst);
                if (disassemble(neighbour.dst, children, Q, src, delta, distance)) {
                    return true;
                }
                children[src].push_back(childrenNodes[neighbour.dst]);
                childrenNodes[neighbour.dst].x = neighbour.dst;
            }
        }
    }
    return false;
}
