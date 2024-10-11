namespace graphs {
    struct Graph {
        i32 n, m;
        vector<vector<i32>> adj;
        Graph(i32 n, i32 m = 0) : n(n), m(m), adj(n), subtreeSize(n, 0) {}
        void addEdge(i32 u, i32 v) { adj[u].push_back(v); adj[v].push_back(u); }
        vector<i32>& operator[] (i32 i) { return adj[i]; }

        // Tarjan's Algorithm: precalculate bridges and subtree sizes of undirected graph
        vector<pair<i64, i64>> bridges;
        vector<i64> subtreeSize;
        void tarjan() {
            vector<bool> visited(n, false);
            vector<i32> disc(n, -1), low(n, -1), parent(n, -1);
            i32 time = 0;

            auto bridgeUtil = [&](i32 u, auto&& bridgeUtil) -> void {
                visited[u] = true;
                disc[u] = low[u] = ++time;
                subtreeSize[u] = 1;
                for (i32 v : adj[u]) {
                    if (!visited[v]) {
                        parent[v] = u;
                        bridgeUtil(v, bridgeUtil);
                        low[u] = min(low[u], low[v]);
                        subtreeSize[u] += subtreeSize[v];
                        if (low[v] > disc[u]) bridges.emplace_back(u, v);
                    } else if (v != parent[u]) {
                        low[u] = min(low[u], disc[v]);
                    }
                }
            };

            for (i32 i = 0; i < n; i++) {
                if (!visited[i]) {
                    bridgeUtil(i, bridgeUtil);
                }
            }
        }
    };
    
    struct DirectedGraph : public Graph {
        DirectedGraph(i64 n, i64 m = 0) : Graph(n, m) {};
        void addEdge(i64 u, i64 v) { adj[u].push_back(v); }

        // Kahn's Algorithm: returns { topological sorted order, is DAG? }
        pair<vector<i32>, bool> topologicalSort() {
            vector<i32> indegree(n, 0);
            for (i32 i = 0; i < n; i++) {
                for (i64 j : adj[i])
                    indegree[j]++;
            }
            queue<i32> q; vector<i32> result;
            for (i32 i = 0; i < n; i++)
                if (!indegree[i]) q.push(i);
            while (!q.empty()) {
                i32 i = q.front(); q.pop(); result.push_back(i);
                for (i32 j : adj[i]) {
                    indegree[j]--;
                    if (!indegree[j]) q.push(j);
                }
            }
            return make_pair(result, result.size() == n);
        }
    };

    struct WeightedGraph {
        i64 n, m;
        vector<vector<pair<i64, i64>>> adj;

        WeightedGraph(i64 n, i64 m = 0) : n(n), m(m), adj(n) {}

        void addEdge(i64 u, i64 v, i64 w) {
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }

        // Dijkstra Algorithm: returns { distances src->i, path src->n }
        pair<vector<i64>, vector<i64>> dijkstra(i64 src) {
            constexpr int INF = 1e17;
            min_heap<pair<i64, i64>> pq;
            vector<i64> dist(n, INF);
            vector<i64> parent(n, -1);
            pq.push(make_pair(0, src));
            dist[src] = 0;
            while (!pq.empty()) {
                i64 u = pq.top().second;
                pq.pop();
                for (auto &i : adj[u]) {
                    i64 v = i.first, w = i.second;
                    if (dist[v] > dist[u] + w) {
                        dist[v] = dist[u] + w;
                        parent[v] = u;
                        pq.push(make_pair(dist[v], v));
                    }
                }
            }
            return {dist, parent};
        }
    };

    bool _graph_oneIndexing = true;
    enum _graph_indexingMode { zeroIndex, oneIndex };
    istream& operator >> (istream& is, enum _graph_indexingMode z) { _graph_oneIndexing = z == oneIndex; return is; }
    istream& operator >> (istream& is, Graph &g) {
        for (i32 i = 0; i < g.m; i++) {
            i32 x, y; is >> x >> y;
            g.addEdge(x-_graph_oneIndexing, y-_graph_oneIndexing);
        }
        return is;
    }

    using Tree = Graph;
    using DirectedTree = DirectedGraph;

    class disjoint_set { 
        i32 n;
        vector<i32> rank, parent, size;
    public:
        disjoint_set(i32 n) : n(n), rank(n, 0), parent(n), size(n, 1) {
            for (i32 i = 0; i < n; i++) parent[i] = i;
        }
        i32 find(i32 x) { 
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        }
        void Union(i32 x, i32 y) { 
            i64 xset = find(x), yset = find(y);
            if (xset == yset) return;

            if (rank[xset] < rank[yset]) {
                parent[xset] = yset;
                size[yset] += size[xset];
            } else if (rank[xset] > rank[yset]) {
                parent[yset] = xset;
                size[xset] += size[yset];
            } else {
                parent[yset] = xset;
                rank[xset]++; 
                size[xset] += size[yset];
            }
        }
        inline i32 sizeOf(i32 x) { return size[find(x)]; }
        inline vector<i32> Set() { vector<i32> ret; for (i32 i = 0; i < n; i++) ret.push_back(find(i)); return ret; }
    };
} using namespace graphs;