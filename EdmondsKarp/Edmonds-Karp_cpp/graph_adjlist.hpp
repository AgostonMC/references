//
// Created by Ágoston Czobor on 2022. 10. 30..
//

#ifndef EDMONDS_KARP_ALGO_GRAPH_ADJLIST_HPP
#define EDMONDS_KARP_ALGO_GRAPH_ADJLIST_HPP

#include <queue>
#include <vector>
#include <list>
#include <iostream>

#define MAX_NODES 50

class AdjList {
    struct Vertex {
        int value;
        int time;
        int capacity;
    };

public:
    int num_nodes;

    std::vector<Vertex> vertecies;
    std::vector<std::list<int>> adj_list;

    Vertex* insert (int value, int time, int capacity) {
        auto* new_node = new Vertex;
        new_node->value = value;
        new_node->time = time;
        new_node->capacity = capacity;
        return new_node;
    }

    AdjList(int num_nodes, int num_edges) : num_nodes(num_nodes) {
        adj_list.resize(num_nodes);
        int from, to, cap, time;
        for (int i = 0; i < num_edges; ++i) {
            std::cin >> from >> to >> time >> cap;
            adj_list[from].push_back(i);
            vertecies.push_back(*insert(to, time, cap));
            //source[to] = insert(from, time, cap, source[to]);
        }
    }

    int parent[MAX_NODES] = {-1};

    bool bfs(int source, int sink) {
        std::queue<int> q;
        std::vector<bool> visited(num_nodes, false);
        q.push(source);
        visited[source] = true;
        parent[source] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            //int curr_flow = 0;
            for (auto adj : adj_list[u]) {
                //curr_flow += adj.capacity;
                if (!visited[adj] && vertecies[adj].capacity > 0) {
                    q.push(adj);
                    visited[adj] = true;
                    parent[adj] = u;
                }
            }
        }
        return visited[sink];
    }

    int edmonds_karp(int source, int sink, int time_limit) {
        int max_flow = 0;
        int max_time = 0;

        while (bfs(source, sink)) {
            std::cout << "bfs" << std::endl;
            int path_flow = INT_MAX;
            int path_time = 0;
            for (int v = sink; v != source; v = parent[v]) {
                if (path_time <= time_limit) {
                    int u = parent[v];
                    auto l_beg = adj_list[u].begin();
                    auto it = std::find(adj_list[u].begin(), adj_list[u].end(), v);
                    int index = std::distance(l_beg, it);
                    path_flow = std::min(path_flow, vertecies[index].capacity);
                    path_time += vertecies[v].time;
                }
            }

            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                vertecies[v].capacity += path_flow;
                vertecies[u].capacity -= path_flow;
            }
            std::cout << "path_flow: " << path_flow << std::endl;
            std::cout << "path_time: " << path_time << std::endl;
            max_flow += path_flow;
            max_time += path_time;
        }

        return max_flow;
    }

    void print_graph() {
        for (int i = 0; i < num_nodes; ++i) {
            std::cout << i << ": ";
            for (auto& v : adj_list[i]) {
                std::cout << vertecies[v].value << " ";
            }
            std::cout << std::endl;
        }
    }

};

#endif //EDMONDS_KARP_ALGO_GRAPH_ADJLIST_HPP
