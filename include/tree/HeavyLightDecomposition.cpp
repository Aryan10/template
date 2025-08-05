#include <bits/stdc++.h>
using namespace std;

template <class SegTree>
struct Tree {
    int n;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy;
    vector<int> head, pos;
    int timer = 0;

    Tree(int n) : n(n), adj(n), parent(n, -1), depth(n, 0), heavy(n, -1), head(n), pos(n) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void heavy_light_decompose() {
        dfs();
        decompose();
    }

    int query(int u, int v, SegTree& st) {
        int res = 0;
        for (; head[u] != head[v]; v = parent[head[v]]) {
            if (depth[head[u]] > depth[head[v]]) 
                swap(u, v);
            res = max(res, st.query(pos[head[v]], pos[v]));
        }
        if (depth[u] > depth[v])
            swap(u, v);
        return max(res, st.query(pos[u], pos[v]));
    }

private:
    int dfs(int u = 0) {
        int size = 1, max_size = 0;
        for (int v : adj[u]) if (v != parent[u]) {
            parent[v] = u, depth[v] = depth[u] + 1;
            int ss = dfs(v);
            size += ss;
            if (ss > max_size)
                max_size = ss, heavy[u] = v;
        }
        return size;
    }

    void decompose(int u = 0, int h = 0) {
        head[u] = h, pos[u] = timer++;
        if (heavy[u] != -1)
            decompose(heavy[u], h);
        for (int v : adj[u])
            if (v != parent[u] and v != heavy[u])
                decompose(v, v);
    }
};