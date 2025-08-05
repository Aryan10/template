#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> euler_tour(vector<vector<int>> const& adj, int root = 0) {
    int n = adj.size();
    vector<pair<int, int>> tour(n);
    
    int timer = 0;
    auto dfs = [&] (auto&& dfs, int u, int p = -1) -> void {
        tour[u].first = timer++;
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs(dfs, v, u);
        }
        tour[u].second = timer - 1;
    }; dfs(dfs, root);

    return tour;
}