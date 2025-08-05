#include <bits/stdc++.h>
using namespace std;

struct FlowNetwork {
    int n;
    vector<vector<int>> adj, residual;
    auto& operator [] (int i) { return adj[i]; }
    
    FlowNetwork(int n) : n(n), adj(n), residual(n, vector<int>(n)) {}

    void addEdge(int u, int v, int capacity = 1, int reverse = 0) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        residual[u][v] += capacity;
        residual[v][u] += reverse;
    }

    vector<int> getAugmentingPath(int source, int sink) {
        vector<int> parent(n, -1);
        vector<bool> reachable(n);
        queue<int> q;

        q.push(source);
        reachable[source] = true;

        while (not q.empty() and not reachable[sink]) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (not reachable[v] and residual[u][v] > 0) {
                    reachable[v] = true;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

        return parent;
    }

    int maxFlow(int source, int sink) {
        int flow = 0;

        while (true) {
            auto parent = getAugmentingPath(source, sink);
            if (parent[sink] == -1) break;

            int pathFlow = numeric_limits<int>::max();
            for (int u = sink; u != source; u = parent[u])
                pathFlow = min(pathFlow, residual[parent[u]][u]);
            
            for (int u = sink; u != source; u = parent[u])
                residual[parent[u]][u] -= pathFlow, 
                residual[u][parent[u]] += pathFlow;

            flow += pathFlow;
        }

        return flow;
    }

    auto minCut(int source, int sink) {
        int flow = maxFlow(0, n - 1);

        vector<bool> reachable(n);
        queue<int> q;
        q.push(source);
        reachable[source] = true;

        while (not q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (not reachable[v] and residual[u][v] > 0) {
                    reachable[v] = true;
                    q.push(v);
                }
            }
        }
        return make_pair(flow, reachable);
    }
};