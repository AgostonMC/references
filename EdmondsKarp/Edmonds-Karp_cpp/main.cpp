#include <iostream>
#include "graph-stuff.hpp"
#include "graph_adjlist.hpp"

//#define AL

#ifndef AL
int main() {
    int n, e, t;

    std::cin >> n >> e >> t;
    Graph g(n, e);
    g.read_graph();

    //g.print_graph();

    int source = 0, sink = n - 1;

    g.print_graph();

    auto res = g.edmonds_karp(source, sink, t);

    std::cout << std::get<0>(res) << " " << std::get<1>(res) << std::endl;

    return 0;
}
#else
int main () {
    int n, e, t;

    std::cin >> n >> e >> t;

    AdjList g(n, e);

    g.print_graph();

    std::cout << g.edmonds_karp(0, n - 1, t) << std::endl;

}


#endif

/*
 * test 1
4 5 3
0 1 1 5
0 2 1 4
1 2 2 2
1 3 1 4
2 3 1 5
 */

/*
 * test 2
4 5 4
0 1 1 5
0 2 1 4
1 2 2 2
1 3 1 4
2 3 1 5
 */