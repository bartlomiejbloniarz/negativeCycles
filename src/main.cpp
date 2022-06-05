#include <iostream>
#include "main.h"
#include <cstring>

#define benchmarkFlag "-b"
#define resultFlag "-r"

using namespace std;

int main(int argc, char** argv) {
    if (argc == 1){
        cout << "Error: no arguments given. Use " << benchmarkFlag << " for benchmark or " << resultFlag << " for result" << endl;
        return 1;
    } else if (!strcmp(argv[1], benchmarkFlag) && !strcmp(argv[1], resultFlag)) {
        cout << "Error: incorrect arguments. Use " << benchmarkFlag << " for benchmark or " << resultFlag << " for result" << endl;
        return 1;
    }
    int z;
    cin>>z;
    bool printResult = !strcmp(argv[1], resultFlag);
    while(z--){
        int n, m, source;
        cin>>n>>m>>source;
        Graph graph(n);
        while(m--){
            int src, dst;
            number weight;
            cin >> src >> dst >> weight;
            graph.addEdge(src, dst, weight);
        }
        clock_t time = clock(); // measures CPU time on Linux
        bool result = containsNegativeCycle(graph, source);
        time = clock() - time;
        if (printResult)
            cout<<result<<endl;
        else
            cout<<time<<endl;
    }
}
