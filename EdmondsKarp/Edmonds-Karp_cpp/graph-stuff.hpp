//
// Created by Ágoston Czobor on 2022. 10. 30..
//

#ifndef EDMONDS_KARP_ALGO_GRAPH_STUFF_HPP
#define EDMONDS_KARP_ALGO_GRAPH_STUFF_HPP

#include <queue>
#include <vector>
#include <iostream>

#define MAX_NODES 50

class Graph {
public:
    int n, e;
    int capacity[MAX_NODES][MAX_NODES]{};
    int flows[MAX_NODES][MAX_NODES]{};
    int times[MAX_NODES][MAX_NODES]{};

    std::vector<int> graph[MAX_NODES];
    int parent[MAX_NODES] ={-1};

    Graph(int n, int e) : n(n), e(e) {};

    void read_graph() {
        int from, to, cap, time;
        for (int i = 0; i < e; ++i) {
            std::cin >> from >> to >> time >> cap;
            graph[from].push_back(to);
            //graph[to].push_back(from);
            capacity[from][to] = cap;
            times[from][to] = time;
        }
    }

    bool bfs(int source, int sink) {
        std::queue<int> q;
        bool visited[MAX_NODES] = {false};
        q.push(source);
        visited[source] = true;
        parent[source] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : graph[u]) {
                if (!visited[v] && capacity[u][v] > flows[u][v]) {
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }
        return visited[sink];
    }

    std::tuple<int, int> edmonds_karp(int source, int sink, int time_limit) {
        int max_flow = 0;
        int max_time = 0;
        while (bfs(source, sink)) {
            int path_flow = INT_MAX;
            int path_time = 0;
            for (int v = sink; v != source; v = parent[v]) {
                std::cout << v << " ";
                if (path_time <= time_limit) {
                    int u = parent[v];
                    path_flow = std::min(path_flow, capacity[u][v] - flows[u][v]);
                    path_time += times[u][v];
                //std::cout << "flow from v to u:: " << path_flow << " " << v << " " << u << std::endl;
                //std::cout << "capacity :: " << capacity[u][v] << std::endl;
                } else {
                    path_flow = 0;
                    break;
                }
            }
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                flows[u][v] += path_flow;
                flows[v][u] -= path_flow;
            }
            std::cout << "EK cycle :" << path_time << " " << path_flow << std::endl;

            // how many can we send in this cycle?

            while (path_time++ <= time_limit) {
                std::cout << "we added " << path_flow << " to max_flow" << std::endl;
                max_flow += path_flow;
                max_time += path_time;
            }
        }
        return std::make_tuple(max_flow, max_time);
    }

    void print_graph() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cout << capacity[i][j] << " " << times[i][j] << " :: ";
            }
            std::cout << std::endl;
        }
    }

};


#endif //EDMONDS_KARP_ALGO_GRAPH_STUFF_HPP
