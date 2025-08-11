#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct MoAlgorithm {
    struct Struct {
        virtual void add(int) = 0;
        virtual void remove(int) = 0;
        virtual T query(void) = 0;
    };

    struct Query {
        int l, r, idx;
    };

    void push_query(int l, int r) {
        queries.push_back({l, r, (int)queries.size()});
    }

    vector<Query> queries;
    vector<int> block_id;
    Struct& ds;

    MoAlgorithm(int n, Struct& ds) : block_id(n), ds(ds) {
        int block_size = sqrt(n) + 1;
        for (int i = 0; i < n; i++)
            block_id[i] = i / block_size;
    }

    /// Mo's algorithm with weighted block decomposition
    MoAlgorithm(int n, Struct& ds, vector<int> const& weight) : block_id(n), ds(ds) {
        int total_weight = accumulate(weight.begin(), weight.end(), 0);
        int K = max((int)1, (int)sqrt(total_weight));
        for (int i = 0, b = 0; i < n; b++) {
            int tot = 0;
            while (i < n && tot < K) {
                tot += weight[i];
                block_id[i++] = b;
            }
        }
    }

    vector<T> operator () () {
        auto comparator = [&] (Query const& a, Query const& b) {
            if (block_id[a.l] != block_id[b.l]) return block_id[a.l] < block_id[b.l];
            return (block_id[a.l] & 1) ? (a.r > b.r) : (a.r < b.r);
        };

        vector<T> answer(queries.size());
        sort(queries.begin(), queries.end(), comparator);
            
        int cur_l = 0, cur_r = -1;
        for (auto const& q : queries) {
            while (cur_l > q.l) ds.add(--cur_l);
            while (cur_r < q.r) ds.add(++cur_r);
            while (cur_l < q.l) ds.remove(cur_l++);
            while (cur_r > q.r) ds.remove(cur_r--);
            answer[q.idx] = ds.query();
        }

        return answer;
    }
};
