namespace graphs {
    template <bool directed = false>
    struct graph {
        int32_t n, m;
        vector<vector<int32_t>> adj;
        graph(i32 n, i32 m = 0) : n(n), m(m), adj(n) {}
        void addEdge(int u, int v) { 
            adj[u].push_back(v); 
            if (!directed) adj[v].push_back(u); 
        }
        auto& operator[] (i32 i) { 
            return adj[i]; 
        }

        // Tarjan's Algorithm: returns bridges and subtree sizes of undirected graph
        pair<vector<pair<i32, i32>>, vector<i32>> tarjan() {
            assert(!directed);
            vector<pair<i32, i32>> bridges;
            vector<i32> subtreeSize(n, 0);
            vector<bool> visited(n, false);
            vector<i32> disc(n, -1), low(n, -1), parent(n, -1);
            i32 time = 0;

            auto dfs = [&](i32 u, auto&& dfs) -> void {
                visited[u] = true;
                disc[u] = low[u] = ++time;
                subtreeSize[u] = 1;
                for (i32 v : adj[u]) {
                    if (!visited[v]) {
                        parent[v] = u;
                        dfs(v, dfs);
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
                    dfs(i, dfs);
                }
            }

            return make_pair(bridges, subtreeSize);
        }

        // Kahn's Algorithm: returns { topological sorted order, isDAG? }
        pair<vector<i32>, bool> topological_sort() {
            assert(directed);
            vector<i32> indegree(n, 0);
            for (i32 i = 0; i < n; i++) {
                for (i32 j : adj[i])
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

    template <bool directed = false>
    struct weighted_graph {
        i32 n, m;
        vector<vector<pair<i32, int>>> adj;

        weighted_graph(int n, int m = 0) : n(n), m(m), adj(n) {}
        void addEdge(i32 u, i32 v, int w) {
            adj[u].emplace_back(v, w);
            if (!directed) adj[v].emplace_back(u, w);
        }
        auto& operator[] (i32 i) { 
            return adj[i]; 
        }

        // Dijkstra Algorithm: returns { distances src->i, shorest path src->n }
        pair<vector<int>, vector<i32>> dijkstra(i32 src) {
            constexpr int _INF = 1e17;
            priority_queue<pair<int, i32>, vector<pair<int, i32>>, greater<pair<int, i32>>> pq;
            vector<int> dist(n, _INF);
            vector<i32> parent(n, -1);
            pq.emplace(0, src);
            dist[src] = 0;
            while (!pq.empty()) {
                int u = pq.top().second;
                pq.pop();
                for (auto [v, w] : adj[u]) {
                    if (dist[v] > dist[u] + w) {
                        dist[v] = dist[u] + w;
                        parent[v] = u;
                        pq.emplace(dist[v], v);
                    }
                }
            }
            return {dist, parent};
        }
    };

    bool _graph_oneIndexing = true;
    enum _graph_indexingMode { zeroIndex, oneIndex };
    istream& operator >> (istream& is, enum _graph_indexingMode z) { _graph_oneIndexing = z == oneIndex; return is; }
    template <bool directed = false> istream& operator >> (istream& is, graph<directed> &g) {
        for (i32 i = 0; i < g.m; i++) {
            i32 x, y; is >> x >> y;
            g.addEdge(x-_graph_oneIndexing, y-_graph_oneIndexing);
        }
        return is;
    }
    template <bool directed = false> istream& operator >> (istream& is, weighted_graph<directed> &g) {
        for (i32 i = 0; i < g.m; i++) {
            i32 x, y; int w; is >> x >> y >> w;
            g.addEdge(x-_graph_oneIndexing, y-_graph_oneIndexing, w);
        }
        return is;
    }

    class disjoint_set { 
        i32 n;
        vector<i32> rank, parent, _size;
    public:
        disjoint_set(int n) : n(n), rank(n, 0), parent(n), _size(n, 1) {
            for (int i = 0; i < n; i++) parent[i] = i;
        }
        int find(int x) { 
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        }
        void unite(int x, int y) {
            x = find(x), y = find(y);
            if (x == y) return;
            if (rank[x] < rank[y]) swap(x, y);
            parent[y] = x;
            _size[x] += _size[y];
            if (rank[x] == rank[y]) rank[x]++;
        }
        inline int size(int x) { 
            return _size[find(x)]; 
        }
        inline vector<int> set() { 
            vector<int> ret;
            for (int i = 0; i < n; i++) 
                ret.push_back(find(i)); 
            return ret;
        }
    };
} using namespace graphs;