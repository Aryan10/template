#include <bits/stdc++.h>
using namespace std;

struct BinaryLifting {
    int n, LOG;
    vector<vector<int>> up;
    vector<int> depth;

    BinaryLifting(vector<vector<int>> const& adj, int root = 0) 
    : n(adj.size()), LOG(bit_width(adj.size())), up(n, vector<int>(LOG, -1)), depth(n, 0) {
        dfs(adj, root);
    }

private:
    void dfs(vector<vector<int>> const& adj, int u, int p = -1) {
        up[u][0] = p;
        for (int i = 1; i < LOG; i++)
            if (up[u][i - 1] != -1)
                up[u][i] = up[up[u][i-1]][i-1];
        for (int v : adj[u]) if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(adj, v, u);
        }
    }

public:
    int getLCA(int u, int v) {
        if (depth[u] < depth[v])
            swap(u, v);

        int diff = depth[u] - depth[v];
        for (int i = 0; i < LOG; i++)
            if (diff & (1 << i))
                u = up[u][i];

        if (u == v) return u;

        for (int i = LOG - 1; i >= 0; i--)
            if (up[u][i] != up[v][i])
                u = up[u][i], v = up[v][i];

        return up[u][0];
    }
};