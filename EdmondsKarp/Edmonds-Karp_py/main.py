# global variables
Source = 0


# read lines and fill up matrices
def read_graph(no_edges, graph, times, capacities, flows):
    for i in range(no_edges):
        edge = [int(item) for item in input().split()]  # from - to - time - capacity
        graph[edge[0]].append(edge[1])
        times[edge[0]][edge[1]].append(int(edge[2]))
        capacities[edge[0]][edge[1]].append(int(edge[3]))
        flows[edge[0]][edge[1]].append(0)
    for i in range(len(graph)):
        for j in range(len(graph)):
            if capacities[i][j] == []:
                capacities[i][j].append(0)
                flows[i][j].append(0)
                times[i][j].append(0)


# BFS with queue and visited list
def bfs(graph, no_nodes, parents, capacities, flows):
    visited = [False] * no_nodes
    queue = [Source]
    visited[Source] = True
    # parents so we can get the path in E-K
    parents[Source] = -1

    while queue:
        node = queue.pop(Source)
        for neighbour in graph[node]:
            if not visited[neighbour]:
                be = capacities[node][neighbour][0] > flows[node][neighbour][0]
                for e in range(1, len(capacities[node][neighbour])):
                    be = be and capacities[node][neighbour][e] > flows[node][neighbour][e]
                if be:
                    visited[neighbour] = True
                    queue.append(neighbour)
                    parents[neighbour] = node

    # if we got to the end, return true
    return visited[no_nodes - 1]


# get the path from parents, so we have an iterable list
def get_parent_list(node, parents):
    parent_list = []
    while node != Source:
        parent_list.append(node)
        node = parents[node]
    return parent_list


# the pain
def edmonds_karp(graph, no_nodes, capacities, flows, times, time_limit, parents):
    max_flow = 0
    # while there is a path from source to sink (bfs true)
    while bfs(graph, no_nodes, parents, capacities, flows):
        # get the path data
        path_flow = float("Inf")
        path_time = 0
        mindinds = []
        # check all nodes from sink to source
        for node in get_parent_list(no_nodes - 1, parents):
            # get the parent of current node, so we have the edge
            nhelp = parents[node]
            # get path data
            val = capacities[nhelp][node][0] - flows[nhelp][node][0]
            minind = 0
            for e in range(1, len(capacities[node][nhelp])):
                tmp = min(val, capacities[nhelp][node][e] - flows[nhelp][node][e])
                if tmp > val:
                    val = tmp
                    minind = e
            if path_time <= time_limit:
                path_flow = min(path_flow, val)
                path_time += times[nhelp][node][minind]
            else:
                path_flow = 0
                break
            mindinds.append(minind)

        # correct the flows matrix, if we use a road, we add the path_flow to it,
        for (node, ind) in zip(get_parent_list(no_nodes - 1, parents), mindinds):
            nhelp = parents[node]

            flows[nhelp][node][ind] += path_flow
            # if we do the funny stuff with going back the edge, we subtract it
            # (I forgot the proper explanation xddd)
            flows[node][nhelp][ind] -= path_flow
        # adjust max_flow, if we have time for multiple trucks, we add the path_flow multiple times
        while path_time <= time_limit:
            max_flow += path_flow
            path_time += 1

    return max_flow


if __name__ == '__main__':
    list1 = input().split()
    N, E, T = [int(item) for item in list1]

    # graph parts:
    # capacities[no_of_nodes][no_of_nodes][]  -- capacity of edge[from][to]
    # flows[no_of_nodes][no_of_nodes][]       -- flow of edge[from][to]
    # times[no_of_nodes][no_of_nodes][]       -- time of edge[from][to]
    # graph[no_of_nodes][no_of_nodes][]       -- adjacency matrix [from][to]
    # parents[no_of_nodes]                  -- parents of nodes in BFS tree

    capacities = [[[] for _ in range(N)] for _ in range(N)]
    flows = [[[] for _ in range(N)] for _ in range(N)]
    times = [[[] for _ in range(N)] for _ in range(N)]
    graph = [[] for i in range(N)]
    parents = [-1] * N

    read_graph(E, graph, times, capacities, flows)

    print(edmonds_karp(graph, N, capacities, flows, times, T, parents))

"""
4 5 3
0 1 1 5
0 2 1 4
1 2 2 2
1 3 1 4
2 3 1 5
"""
