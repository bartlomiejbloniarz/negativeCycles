#include <iostream>
#include "main.h"
#include <cstring>

#define timeFlag "-t"
#define labelingCountFlag "-c"

using namespace std;

int main(int argc, char** argv) {
    if (argc == 1){
        cout << "Error: no arguments given. Use " << timeFlag << " for time or " << labelingCountFlag << " for labeling count" << endl;
        return 1;
    } else if (!strcmp(argv[1], timeFlag) && !strcmp(argv[1], labelingCountFlag)) {
        cout << "Error: incorrect arguments. Use " << timeFlag << " for time or " << labelingCountFlag << " for labeling count" << endl;
        return 1;
    }
    int z;
    cin>>z;
    bool printTime = !strcmp(argv[1], timeFlag);
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
        number labelingCount=0;
        clock_t time = clock(); // measures CPU time on Linux
        bool result = containsNegativeCycle(graph, source, labelingCount);
        time = clock() - time;
        cout<<result<<endl;
        if (printTime)
            cerr<<time<<endl;
        else
            cerr<<labelingCount<<endl;
    }
}
