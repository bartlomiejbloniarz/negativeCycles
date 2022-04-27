#ifndef CODE_UTIL_H
#define CODE_UTIL_H

#include <vector>

#define INFINITY INT_MAX/2

using namespace std;

// walk to the root
// returns true if dst is an ancestor of src
bool isAncestor(vector<int>& predecessor, int src, int dst, int source){
    while (src != source && src != dst)
        src = predecessor[src];
    return src == dst;
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

#endif //CODE_UTIL_H
