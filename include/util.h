#ifndef CODE_UTIL_H
#define CODE_UTIL_H

#include <vector>

using namespace std;

// walk to the root
// returns true if dst is an ancestor of src
bool isAncestor(vector<int>& predecessor, int src, int dst, int source){
    while (src != source && src != dst)
        src = predecessor[src];
    return src == dst;
}

bool dfs(int v, vector<int>& predecessor, vector<int> &visited){
    visited[v] = 1;
    int w = predecessor[v];
    if (w == -1 || visited[w] == 2) {
        visited[v] = 2;
        return false;
    }
    if (visited[w] == 1)
        return true;

    bool result = dfs(w, predecessor, visited);
    visited[v] = 2;
    return result;
}

bool predecessorGraphContainsCycle(vector<int>& predecessor, int n){
    vector<int> visited(n, 0);
    for (int v=0; v<n; v++){
        if (!visited[v]){
            bool res = dfs(v, predecessor, visited);
            if (res)
                return true;
        }
    }
    return false;
}

struct counter{
    int n, c=1;
    explicit counter(int n): n(n){};
    void increment(){
        c++;
        c%=n;
    }
    bool isActive(){
        return c == 0;
    }
};

struct LinkedListNode {
    LinkedListNode *next, *prev;
    int x;
    explicit LinkedListNode(int x=-1, LinkedListNode *prev = nullptr, LinkedListNode *next = nullptr): next(next), prev(prev), x(x){}
    void unlink(){
        next->prev = prev;
        prev->next = next;
        next = nullptr;
        prev = nullptr;
    }
};

struct LinkedList{
    LinkedListNode *head, *tail;
    explicit LinkedList(){
        head = new LinkedListNode(-1);
        tail = new LinkedListNode(-1, head, nullptr);
        head->next = tail;
    }
    void push_front(LinkedListNode &node){
        node.next = head->next;
        node.prev = head;
        head->next->prev = &node;
        head->next = &node;
    }
    LinkedListNode* pop_front(){
        LinkedListNode* node = head->next;
        node->unlink();
        return node;
    }
    void push_back(LinkedListNode &node){
        node.prev = tail->prev;
        node.next = tail;
        tail->prev->next = &node;
        tail->prev = &node;
    }
    LinkedListNode* pop_back(){
        LinkedListNode* node = tail->prev;
        node->unlink();
        return node;
    }
    bool isEmpty(){
        return head->next == tail;
    }
    ~LinkedList(){
        delete head;
        delete tail;
    }
};

struct Set{
    int n;
    LinkedListNode *nodes;
    LinkedList list;
    explicit Set(int n): n(n), list(){
        nodes = new LinkedListNode[n];
    }
    void insert(int x){
        if (!contains(x)){
            nodes[x].x=x;
            list.push_back(nodes[x]);
        }
    }
    void erase(int x){
        if (contains(x)){
            nodes[x].x = -1;
            nodes[x].unlink();
        }
    }
    bool contains(int x) const{
        return nodes[x].x == x;
    }
    bool isEmpty(){
        return list.isEmpty();
    }
    void clear(){
        for (LinkedListNode* node = list.head->next; node != list.tail; ) {
            int x = node->x;
            node = node->next;
            nodes[x].x = -1;
            nodes[x].unlink();
        }

    }
    ~Set(){
        delete [] nodes;
    }
};

struct Queue{
    int n;
    LinkedListNode *nodes;
    LinkedList list;
    Queue(int n): n(n), list(){
        nodes = new LinkedListNode[n];
    }
    void push(int x){
        if (nodes[x].x == -1){
            nodes[x].x = x;
            list.push_back(nodes[x]);
        }
    }
    int pop(){
        auto node = list.pop_front();
        int x = node->x;
        node->x = -1;
        return x;
    }
    void remove(int x){
        if (nodes[x].x == x){
            nodes[x].unlink();
            nodes[x].x = -1;
        }
    }
    bool isEmpty(){
        return list.isEmpty();
    }
    ~Queue(){
        delete [] nodes;
    }
};

#endif //CODE_UTIL_H
