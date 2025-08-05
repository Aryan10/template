#include <bits/stdc++.h>
using namespace std;

template <bool directed = false>
struct Graph {
    int n;
    vector<vector<int>> adj;
    auto& operator [] (int i) { return adj[i]; }

    Graph(int n) : n(n), adj(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        if (not directed) adj[v].push_back(u);
    }

    void input(int edges, int offset = 0) {
        while (edges--) {
            int u, v;
            cin >> u >> v;
            addEdge(u - offset, v - offset);
        }
    }

    void input(vector<vector<int>>& edges, int offset = 0) {
        for (auto& e : edges)
            addEdge(e[0] - offset, e[1] - offset);
    }
};

template <bool directed = false>
struct WeightedGraph {
    int n;
    vector<vector<pair<int, int>>> adj;
    auto& operator [] (int i) { return adj[i]; }

    WeightedGraph(int n) : n(n), adj(n) {}

    void addEdge(int u, int v, int w) {
        adj[u].emplace_back(v, w);
        if (not directed) adj[v].emplace_back(u, w);
    }

    void input(int edges, int offset = 0) {
        while (edges--) {
            int u, v, w;
            cin >> u >> v >> w;
            addEdge(u - offset, v - offset, w);
        }
    }

    void input(vector<vector<int>>& edges, int offset = 0) {
        for (auto& e : edges)
            addEdge(e[0] - offset, e[1] - offset, e[2]);
    }
};